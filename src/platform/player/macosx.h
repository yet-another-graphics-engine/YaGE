#include "../player.h"

@class AVAudioPlayer;
@class NSData;

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
