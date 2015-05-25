#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

namespace yage {
namespace audio {
class Player {
    protected:
        std::string url_;  ///< URL of the music to play
    public:
        Player();
        virtual ~Player() = 0;
        /**
         * @brief Play the music in the Player
         * @return The status if music plays normally
         */
        virtual bool play(void) = 0;
        /**
         * @brief Pause the music in the Player
         */
        virtual void pause(void) = 0;
        /**
         * @brief Stop the music in the Player
         */
        virtual void stop(void) = 0;
        /**
         * @brief Get if the music is playing
         * @return The status if music is playung
         */
        virtual bool is_playing(void) = 0;

        /**
         * @brief Creates a new instance of Player (Factory method)
         * @param url The URL of music to be played
         * @return Player instance created
         */
        static Player *create_player(std::string url);
};

}
}
#endif // PLAYER_H_
