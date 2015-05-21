#include "test.h"
#include "../audio/player.h"

void test_audio(void) {
    using yage::audio::Player;
    std::cerr << "Playing test track" << std::endl;
    Player *p = Player::create_player("file:///home/hugh/tmp/t.mp3");
    p->play();
    while(p->is_playing()) sleep_sec(1);
    std::cerr << "Test track stopped" << std::endl;

    std::cerr << "Load file IGNITE from Internet" << std::endl;
    Player *player = Player::create_player("https://kirito.me/ignite.mp3");
    std::cerr << "Play IGNITE" << std::endl;
    player->play();
    sleep_sec(5);

    std::cerr << "Load file Date A Live from Internet" << std::endl;
    Player *player2 = Player::create_player("https://kirito.me/date_a_live.mp3");
    std::cerr << "Play Date A Live" << std::endl;
    player2->play();
    sleep_sec(3);

    std::cerr << "Pause IGNITE" << std::endl;
    player->pause();
    sleep_sec(3);

    player->play();
    std::cerr << "Resume IGNITE" << std::endl;
    sleep_sec(3);

    std::cerr << "Stop IGNITE" << std::endl;
    player->stop();
    std::cerr << "Play IGNITE" << std::endl;
    player->play();
    sleep_sec(3);

    std::cerr << "Destroy music IGNITE object" << std::endl;
    delete player;
    sleep_sec(2);

    std::cerr << "Stop Date A Live" << std::endl;
    player2->stop();
    std::cerr << "Destroy music Date A Live object" << std::endl;
    delete player2;
}


