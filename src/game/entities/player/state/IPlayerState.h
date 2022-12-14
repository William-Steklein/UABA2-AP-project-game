#ifndef GAME_ENGINE_IPLAYERSTATE_H
#define GAME_ENGINE_IPLAYERSTATE_H


#include <memory>

#include "game/entities/player/Player.h"

namespace game {

    class Player;

    class IPlayerState {
    public:
        virtual ~IPlayerState() = default;

        virtual void enter(Player &player) {};

        virtual void exit(Player &player) {};

        virtual void physicsUpdate(game::Player &player) {};

        virtual void graphicsUpdate(Player &player) {};

        virtual void handleInput(Player &player, const InputEvent &input) {
            if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                switch (input.type) {
                    case InputEvent::Type::LEFT:
                        player.updateDirection(Player::Direction::LEFT);
                        break;

                    case InputEvent::Type::RIGHT:
                        player.updateDirection(Player::Direction::RIGHT);
                        break;

                    default:
                        break;
                }
            }
        };

    protected:
        IPlayerState() = default;
    };

} // game

#endif //GAME_ENGINE_IPLAYERSTATE_H