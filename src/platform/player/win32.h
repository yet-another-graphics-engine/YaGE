#ifndef PLAYER_WIN32_H_
#define PLAYER_WIN32_H_
#include "../player.h"

#include <windows.h>
#include <wmp.h>
#include <atlbase.h>

namespace yage {
namespace platform {

class WinPlayer : public Player {
private:
	static DWORD WINAPI player_worker_(LPVOID lpParameter);
	template <class T>
	static T * addressof_(T & v) {
		return reinterpret_cast<T *>(&const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
	}
	bool finished_;
	DWORD thread_id_;
	HANDLE thread_handle_;
	CComPtr<IWMPPlayer> player_;
	CComPtr<IWMPControls> control_;

public:
	WinPlayer(std::string url);
	virtual ~WinPlayer();
	virtual bool play(void);
	virtual void pause(void);
	virtual void stop(void);
	virtual bool is_playing(void);
};

}
}

#endif

