#include "../util/encoding.h"
#include "mswin.h"
#include <cassert>
#include <iostream>

namespace yage {
namespace audio {

static const UINT YAGE_PLAYER_MESSAGE = WM_USER + 0x233;
static const WPARAM YAGE_PLAYER_PLAY = 1L;
static const WPARAM YAGE_PLAYER_PAUSE = 2L;
static const WPARAM YAGE_PLAYER_STOP = 3L;
static const WPARAM YAGE_PLAYER_PLAYING = 4L;
static const WPARAM YAGE_PLAYER_FINALIZE = 5L;

struct player_init_message {
    WinPlayer* this_;
    std::string url;
    HANDLE event_;
};

// Structure to be sent to thread
struct player_callback_message {
    HANDLE event_;
    bool *pbool_;
};

DWORD WINAPI WinPlayer::player_worker_(LPVOID lpParameter) {

    player_init_message *init_msg = (player_init_message *)lpParameter;

    MSG msg;
    HRESULT hr;
    WinPlayer *this_ = init_msg->this_;
    bool *pfinished = &this_->finished_;
    IWMPPlayer *player;
    IWMPControls *controls;

    // WinPlayer instance ctor
    CoInitialize(NULL);
    IID iid_wmpplayer;
    IIDFromString(const_cast<wchar_t *>(L"{6bf52a4f-394a-11d3-b153-00c04f79faa6}"), &iid_wmpplayer);
    UUID uuid_windowsmediaplayer;
    IIDFromString(const_cast<wchar_t *>(L"{6BF52A52-394A-11d3-B153-00C04F79FAA6}"), &uuid_windowsmediaplayer);
    hr = CoCreateInstance(uuid_windowsmediaplayer, 0, CLSCTX_INPROC_SERVER, iid_wmpplayer, (void **)&this_->player_);
    player = this_->player_;
    assert(SUCCEEDED(hr));
    wchar_t *wurl = yage::util::ansi_to_utf_16(init_msg->url.c_str());
    hr = IWMPPlayer_put_URL(player, wurl);
    assert(SUCCEEDED(hr));
    free(wurl);
    hr = IWMPPlayer_get_controls(player, &this_->control_);
    controls = this_->control_;
    assert(SUCCEEDED(hr));
    SetEvent(init_msg->event_);

    while (true) {
        if (!*pfinished) {
            if (GetMessageW(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
                if (msg.message == YAGE_PLAYER_MESSAGE) {
                    player_callback_message *cb_msg = (player_callback_message *)msg.lParam;
                    switch (msg.wParam) {
                    case YAGE_PLAYER_PLAY:
                        hr = IWMPControls_play(controls);
                        assert(SUCCEEDED(hr));
                        *cb_msg->pbool_ = SUCCEEDED(hr);
                        break;

                    case YAGE_PLAYER_PAUSE:
                        hr = IWMPControls_pause(controls);
                        assert(SUCCEEDED(hr));
                        break;

                    case YAGE_PLAYER_STOP:
                        hr = IWMPControls_stop(controls);
                        assert(SUCCEEDED(hr));
                        break;

                    case YAGE_PLAYER_PLAYING:
                        WMPPlayState wmpps;
                        hr = IWMPPlayer_get_playState(player, &wmpps);
                        assert(SUCCEEDED(hr));
                        *cb_msg->pbool_ = wmpps == wmppsPlaying;
                        break;

                    case YAGE_PLAYER_FINALIZE:
                        *pfinished = true;
                        break;

                    default:
                        std::cerr << "Triggered default!" << std::endl;
                    }
                    SetEvent(cb_msg->event_);
                }
            }
        } else {
            break;
        }
        CoUninitialize();
    }
    return 0;
}

WinPlayer::WinPlayer(std::string url) : Player() {
    finished_ = false;
    url_ = url;
    HRESULT hr = S_OK;
    player_init_message msg;
    msg.this_ = this;
    msg.url = url;
    msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
    thread_handle_ = CreateThread(NULL, 0, player_worker_, (LPVOID) &msg, 0L, &thread_id_);
    WaitForSingleObject(msg.event_, INFINITE);
    CloseHandle(msg.event_);
}


WinPlayer::~WinPlayer() {
    IWMPControls_Release(control_);
    IWMPPlayer_Release(player_);
    send_message_(YAGE_PLAYER_FINALIZE);
    WaitForSingleObject(thread_handle_, INFINITE);
    CloseHandle(thread_handle_);
}

bool WinPlayer::send_message_(WPARAM message) {
    bool result;
    player_callback_message msg;
    msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
    msg.pbool_ = &result;
    PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, message, (LPARAM)&msg);
    WaitForSingleObject(msg.event_, INFINITE);
    CloseHandle(msg.event_);
    return result;
}

bool WinPlayer::play() {
    return send_message_(YAGE_PLAYER_PLAY);
}

void WinPlayer::pause() {
    send_message_(YAGE_PLAYER_PAUSE);
}

void WinPlayer::stop() {
    send_message_(YAGE_PLAYER_STOP);
}

bool WinPlayer::is_playing() {
    return send_message_(YAGE_PLAYER_PLAYING);
}

}
}

