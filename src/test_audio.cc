#include "platform/player.h"
#include <unistd.h>
//#include <string>
int main(void) {
    using yage::platform::Player;
    Player *player = Player::create_player("/Users/kirito/Desktop/ALTIMA - Burst The Gravity.mp3");
    player->play();
    sleep(50);
    player->stop();
}
