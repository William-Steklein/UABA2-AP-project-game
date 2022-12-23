#ifndef GAME_ENGINE_IPLAYERSTATE_H
#define GAME_ENGINE_IPLAYERSTATE_H

#include <memory>

#include "game/entities/player/Player.h"

namespace game {
    class IPlayerState {
    public:
        virtual ~IPlayerState() = default;

        virtual void enter() {};

        virtual void exit() {};

        virtual void physicsUpdate() {};

        virtual void graphicsUpdate() {};

        virtual void handleInput(const InputEvent &input) {
            if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                switch (input.type) {
                    case InputEvent::Type::LEFT:
                        _player.updateDirection(Player::Direction::LEFT);
                        break;

                    case InputEvent::Type::RIGHT:
                        _player.updateDirection(Player::Direction::RIGHT);
                        break;

                    default:
                        break;
                }
            }
        };

//    protected:
        IPlayerState(Player &player) : _player(player) {};

        Player &_player;
    };

} // game

#endif //GAME_ENGINE_IPLAYERSTATE_H
