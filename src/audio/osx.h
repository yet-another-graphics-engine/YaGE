#ifndef AUDIO_OSX_H_
#define AUDIO_OSX_H_

#include "player.h"

#ifdef __OBJC__
@class AVPlayer;
#else
struct AVPlayer;
#error An Objective-C++ compiler is required. Add "-ObjC++" in your CFLAGS and "-framework Foundation -framework AVFoundation" in your LDFLAGS.
#endif

namespace yage {
namespace audio {
class OSXPlayer : public Player {
    private:
        AVPlayer *player_; ///< AVPlayer Object instance
    public:
        OSXPlayer(std::string url);
        virtual ~OSXPlayer();
        virtual bool play();
        virtual void pause();
        virtual void stop();
        virtual bool is_playing();
        virtual void seek(double seconds);
};

}
}

#endif
