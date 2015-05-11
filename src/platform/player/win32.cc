#include "win32.h"
#include <cassert>
#include <iostream>

namespace yage {

namespace util {

wchar_t *char_to_wchar(const char *str) {
    int length = strlen(str) + 1;
    wchar_t *t = new wchar_t[length];
    memset(t, 0, length * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, str, strlen(str), t, length);
    return t;
}

}

namespace platform {

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
    hr = this_->player_.CoCreateInstance(__uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER);
    player = this_->player_;
    assert(SUCCEEDED(hr));
    wchar_t *wurl = yage::util::char_to_wchar(init_msg->url.c_str());
    hr = player->put_URL(wurl);
    assert(SUCCEEDED(hr));
    delete[] wurl;
    hr = player->get_controls(&(this_->control_));
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
                        hr = controls->play();
                        assert(SUCCEEDED(hr));
                        *cb_msg->pbool_ = SUCCEEDED(hr);
                        break;

                    case YAGE_PLAYER_PAUSE:
                        hr = controls->pause();
                        assert(SUCCEEDED(hr));
                        break;

                    case YAGE_PLAYER_STOP:
                        hr = controls->stop();
                        assert(SUCCEEDED(hr));
                        break;

                    case YAGE_PLAYER_PLAYING:
                        WMPPlayState wmpps;
                        hr = player->get_playState(&wmpps);
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
    thread_handle_ = CreateThread(NULL, 0, player_worker_, (LPVOID) &msg, NULL, &thread_id_);
    WaitForSingleObject(msg.event_, INFINITE);
    CloseHandle(msg.event_);
}


WinPlayer::~WinPlayer() {
    control_.Release();
    player_.Release();
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

