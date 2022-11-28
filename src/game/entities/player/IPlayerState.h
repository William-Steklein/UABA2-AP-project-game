#ifndef GAME_ENGINE_IPLAYERSTATE_H
#define GAME_ENGINE_IPLAYERSTATE_H


#include <memory>
#include <string>

#include "game/InputEvent.h"

namespace game {

    class Player;

    class IPlayerState {
    public:
        virtual ~IPlayerState() = default;

        virtual void enter(Player &player) = 0;

        virtual void update(Player &player) = 0;
        
        virtual std::shared_ptr<IPlayerState> handleInput(Player &player, const InputEvent &input) = 0;
    };

} // game

#endif //GAME_ENGINE_IPLAYERSTATE_H
