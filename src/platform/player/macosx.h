#include "../player.h"

@class AVAudioPlayer;

namespace yage {
namespace platform {
class OSXPlayer : public Player {
    private:
        AVAudioPlayer *player_;
    public:
        OSXPlayer(std::string url);
        virtual bool play();
        virtual void pause();
        virtual void stop();
        virtual bool is_playing();
};

}
}
