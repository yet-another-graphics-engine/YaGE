#include "player.h"
#if defined(__APPLE__)
#include "osx.h"
#elif defined(_WIN32)
#include "mswin.h"
#else
#include "unix.h"
#endif

namespace yage {
namespace audio {

Player::Player() {}
Player::~Player() {}

Player *Player::create_player(std::string url) {
#if defined(__APPLE__)
    return new OSXPlayer(url);
#elif defined(_WIN32)
    return new WinPlayer(url);
#else
    return new UnixPlayer(url);
#endif
}

}
}
