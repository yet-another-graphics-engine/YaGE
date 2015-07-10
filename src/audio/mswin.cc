#include "../util/encoding.h"
#include "mswin.h"
#include <cassert>
#include <iostream>

namespace yage {
namespace audio {

/**
 * @brief Windows Message code of YaGE Audio Player
 */
static const UINT YAGE_PLAYER_MESSAGE = WM_USER + 0x233;

/**
 * @brief Signal to send to player worker thread
 */
enum YAGE_PLAY_SIGNAL {YAGE_PLAYER_UNKNOWN, YAGE_PLAYER_PLAY, YAGE_PLAYER_PAUSE, YAGE_PLAYER_STOP, YAGE_PLAYER_PLAYING, YAGE_PLAYER_SEEK, YAGE_PLAYER_FINALIZE};

/**
 * @brief Initial information for player worker thread
 */
struct player_init_message {
    WinPlayer* this_;  ///< the pointer pointing to `this` player
    std::string url;   ///< URL that be played later
    HANDLE event_;     ///< Event that waits for finish of initialization
};

/**
 * @brief Signal information to be sent to player worker thread
 */
struct player_callback_message {
    HANDLE event_;     ///< Event that waits for finish of operation process
    void *pvoid_;      ///< (optional) Return value that player returns
};

/**
 * @brief Player worker thread of the player
 *
 * See https://msdn.microsoft.com/en-us/library/windows/desktop/ms686736(v=vs.85).aspx for more information of
 * this function
 *
 * @param lpParameter Signal information sent to thread
 * @return 0 if thread gracefully finished
 */
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

    // Message loop
    while (true) {
        if (!*pfinished) {
            if (GetMessageW(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
                // Deal with YAGE_PLAYER_* messages
                if (msg.message == YAGE_PLAYER_MESSAGE) {
                    player_callback_message *cb_msg = (player_callback_message *)msg.lParam;
                    switch (msg.wParam) {
                    case YAGE_PLAYER_PLAY:
                        hr = IWMPControls_play(controls);
                        assert(SUCCEEDED(hr));
                        *reinterpret_cast<bool *>(cb_msg->pvoid_) = SUCCEEDED(hr);
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
                        *reinterpret_cast<bool *>(cb_msg->pvoid_) = wmpps == wmppsPlaying;
                        break;

                    case YAGE_PLAYER_FINALIZE:
                        *pfinished = true;
                        break;

                    case YAGE_PLAYER_SEEK:
                        hr = IWMPControls_put_currentPosition(controls, *reinterpret_cast<double *>(cb_msg->pvoid_));
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

/**
 * @brief Creates a new instance of WinPlayer
 * @param url The URL of music to be played
 */
WinPlayer::WinPlayer(std::string url) : Player() {
    finished_ = false;
    url_ = url;
    player_init_message msg;
    msg.this_ = this;
    msg.url = url;
    msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
    thread_handle_ = CreateThread(NULL, 0, player_worker_, (LPVOID) &msg, 0L, &thread_id_);
    WaitForSingleObject(msg.event_, INFINITE);
    CloseHandle(msg.event_);
}

/**
 * @brief Destructor of WinPlayer
 */
WinPlayer::~WinPlayer() {
    IWMPControls_Release(control_);
    IWMPPlayer_Release(player_);
    send_message_(YAGE_PLAYER_FINALIZE);
    WaitForSingleObject(thread_handle_, INFINITE);
    CloseHandle(thread_handle_);
}

/**
 * @brief Send a message to worker thread
 * @param message The message to be sent to thread
 * @return Desired return value got from worker thread
 */
void WinPlayer::send_message_(WPARAM message, void *info) {
    player_callback_message msg;
    msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
    msg.pvoid_ = info;
    PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, message, (LPARAM)&msg);
    WaitForSingleObject(msg.event_, INFINITE);
    CloseHandle(msg.event_);
}

/**
 * @brief Play the music in the Player
 * @return The status if music plays normally
 */
bool WinPlayer::play() {
    bool ret = false;
    send_message_(YAGE_PLAYER_PLAY, &ret);
    return ret;
}

/**
 * @brief Pause the music in the Player
 */
void WinPlayer::pause() {
    send_message_(YAGE_PLAYER_PAUSE);
}

/**
 * @brief Stop the music in the Player
 */
void WinPlayer::stop() {
    send_message_(YAGE_PLAYER_STOP);
}

/**
 * @brief Get if the music is playing
 * @return The status if music is playing
 */
bool WinPlayer::is_playing() {
    bool ret = false;
    send_message_(YAGE_PLAYER_PLAYING, &ret);
    return ret;
}

void WinPlayer::seek(double seconds) {
    send_message_(YAGE_PLAYER_SEEK, &seconds);
}

}
}

