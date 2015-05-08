#include "player.h"
//#if defined(__APPLE__)
#include "player/macosx.h"
//#endif

namespace yage {
namespace platform {

Player::Player() {}

Player *Player::create_player(std::string url) {
#if defined(__APPLE__)
    return new OSXPlayer(url);
#endif
}

}
}
