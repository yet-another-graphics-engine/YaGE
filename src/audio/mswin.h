#ifndef AUDIO_MSWIN_H_
#define AUDIO_MSWIN_H_
#include "player.h"

#include <windows.h>

#ifdef __MINGW32__
#include "mswin_wmp_mingw.h"
#else
#define CINTERFACE
#define COBJMACROS
#include <wmp.h>
#endif

namespace yage {
namespace audio {

class WinPlayer : public Player {
private:
    static DWORD WINAPI player_worker_(LPVOID lpParameter);

    bool finished_;          ///< Status that indicates the player thread is to be terminated
    DWORD thread_id_;        ///< Thread ID of player worker thread
    HANDLE thread_handle_;   ///< Thread handle of player worker thread
    IWMPPlayer *player_;     ///< Windows Media Player Object instance
    IWMPControls *control_;  ///< Windows Media Player Control Object instance
    void send_message_(WPARAM message, void *info = NULL);

public:
    WinPlayer(std::string url);
    virtual ~WinPlayer();
    virtual bool play(void);
    virtual void pause(void);
    virtual void stop(void);
    virtual bool is_playing(void);
    virtual void seek(double seconds);
};

}
}

#endif

