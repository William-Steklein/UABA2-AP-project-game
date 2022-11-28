#ifndef GAME_ENGINE_PLAYERSTATE_H
#define GAME_ENGINE_PLAYERSTATE_H


#include "engine/logging/Logger.h"

#include "game/entities/player/IPlayerState.h"
#include "game/entities/player/Player.h"

namespace game {

    class IdleState : public IPlayerState {
    public:
        IdleState();

        ~IdleState() override = default;

        void enter(game::Player &player) override;

        void update(game::Player &player) override;

        std::shared_ptr<IPlayerState> handleInput(game::Player &player, const std::string &input) override;
    };

} // game

#endif //GAME_ENGINE_PLAYERSTATE_H
