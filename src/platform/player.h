#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

namespace yage {
namespace platform {
class Player {
    protected:
        std::string url_;
    public:
        Player();
        virtual bool play(void) = 0;
        virtual void pause(void) = 0;
        virtual void stop(void) = 0;
        virtual bool is_playing(void) = 0;

        static Player *create_player(std::string url);
};

}
}
#endif // PLAYER_H_
