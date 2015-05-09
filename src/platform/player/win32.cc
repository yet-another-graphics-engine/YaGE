#include "win32.h"
#include <cassert>
#include <iostream>

namespace yage {

namespace util {
wchar_t* char_to_wchar(const char *str) {
	int length = strlen(str) + 1;
	wchar_t *t = new wchar_t[length];
	memset(t, 0, length*sizeof(wchar_t));
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


struct player_init_message {
	WinPlayer* this_;
	std::string url;
	CComPtr<IWMPPlayer> *pplayer_;
	CComPtr<IWMPControls> *pcontrols_;
	HANDLE event_;
};

// Structure to be sent to thread
struct player_callback_message {
	HANDLE event_;
	bool *pbool_;
};

DWORD WINAPI WinPlayer::player_msg_proc_(LPVOID lpParameter) {

	player_init_message *init_msg = (player_init_message *)lpParameter;

	MSG msg;
	HRESULT hr;
	WinPlayer *this_ = init_msg->this_;
	bool *pfinished = &this_->finished_;
	IWMPPlayer *player;
	IWMPControls *controls;

	// WinPlayer instance ctor
	CoInitialize(NULL);
	hr = init_msg->pplayer_->CoCreateInstance(__uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER);
	player = *init_msg->pplayer_;
	assert(SUCCEEDED(hr));
	wchar_t *wurl = yage::util::char_to_wchar(init_msg->url.c_str());
	hr = player->put_URL(wurl);
	assert(SUCCEEDED(hr));
	delete[] wurl;
	hr = player->get_controls(init_msg->pcontrols_->operator&());
	controls = *init_msg->pcontrols_;
	controls->play();
	assert(SUCCEEDED(hr));
	SetEvent(init_msg->event_);

	while (true) {
		if (!*pfinished) {
			if (GetMessageW(&msg, NULL, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
				std::cout << std::hex << msg.message << std::endl;
				if (msg.message == YAGE_PLAYER_MESSAGE) {
					switch (msg.wParam) {
					case YAGE_PLAYER_PLAY:
						hr = controls->play();
						assert(SUCCEEDED(hr));
						*((player_callback_message*)msg.lParam)->pbool_ = SUCCEEDED(hr);
						SetEvent(((player_callback_message*)msg.lParam)->event_);
						break;

					case YAGE_PLAYER_PAUSE:
						hr = controls->pause();
						assert(SUCCEEDED(hr));
						SetEvent(((player_callback_message*)msg.lParam)->event_);
						break;
						
					case YAGE_PLAYER_STOP:
						hr = controls->stop();
						assert(SUCCEEDED(hr));
						SetEvent(((player_callback_message*)msg.lParam)->event_);
						break;

					case YAGE_PLAYER_PLAYING:
						WMPPlayState wmpps;
						hr = player->get_playState(&wmpps);
						*((player_callback_message*)msg.lParam)->pbool_ = wmpps == wmppsPlaying;
						SetEvent(((player_callback_message*)msg.lParam)->event_);
						break;

					default:
						std::cerr << "Triggered default!" << std::endl;
					}
				}
			}
		} else {
			break;
		}
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
	msg.pplayer_ = addressof_(player_);
	msg.pcontrols_ = addressof_(control_);
	msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
	thread_handle_ = CreateThread(NULL, 0, player_msg_proc_, (LPVOID) &msg, NULL, &thread_id_);
	WaitForSingleObject(msg.event_, INFINITE);
}


WinPlayer::~WinPlayer() {
	finished_ = true;
	control_.Release();
	player_.Release();
}

bool WinPlayer::play() {
	bool result;
	player_callback_message msg;
	msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
	msg.pbool_ = &result;
	PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, YAGE_PLAYER_PLAY, (LPARAM)&msg);
	WaitForSingleObject(msg.event_, INFINITE);
	return result;
}

void WinPlayer::pause() {
	player_callback_message msg;
	msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
	PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, YAGE_PLAYER_PAUSE, (LPARAM)&msg);
	WaitForSingleObject(msg.event_, INFINITE);	
}

void WinPlayer::stop() {
	player_callback_message msg;
	msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
	PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, YAGE_PLAYER_STOP, (LPARAM)&msg);
	WaitForSingleObject(msg.event_, INFINITE);
}

bool WinPlayer::is_playing() {
	bool result;
	player_callback_message msg;
	msg.event_ = CreateEventW(NULL, FALSE, FALSE, NULL);
	msg.pbool_ = &result;
	PostThreadMessageW(thread_id_, YAGE_PLAYER_MESSAGE, YAGE_PLAYER_PLAYING, (LPARAM)&msg);
	WaitForSingleObject(msg.event_, INFINITE);
	return result;
}

}
}

