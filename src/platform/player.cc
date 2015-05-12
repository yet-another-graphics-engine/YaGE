#include "player.h"
#if defined(__APPLE__)
#include "player/macosx.h"
#elif defined(_WIN32)
#include "player/win32.h"
#else
#include "player/linux.h"
#endif

namespace yage {
namespace platform {

Player::Player() {}
Player::~Player() {}

Player *Player::create_player(std::string url) {
#if defined(__APPLE__)
    return new OSXPlayer(url);
#elif defined(_WIN32)
    return new WinPlayer(url);
#else
    return new LinuxPlayer(url);
#endif
}

}
}
