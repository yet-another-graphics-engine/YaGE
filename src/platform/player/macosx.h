#ifndef PLAYER_MACOSX_H_
#define PLAYER_MACOSX_H_

#include "../player.h"

#ifdef __OBJC__
@class AVAudioPlayer;
@class NSData;
#else
#error An Objective-C++ compiler is required. Add "-ObjC++" in your CFLAGS and "-framework Foundation -framework AVFoundation" in your LDFLAGS.
#endif

namespace yage {
namespace platform {
class OSXPlayer : public Player {
    private:
        AVAudioPlayer *player_;
        //NSError *error_;
        NSData *content_;
    public:
        OSXPlayer(std::string url);
        virtual ~OSXPlayer();
        virtual bool play();
        virtual void pause();
        virtual void stop();
        virtual bool is_playing();
};

}
}

#endif
