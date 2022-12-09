#ifndef GAME_ENGINE_IDLESTATE_H
#define GAME_ENGINE_IDLESTATE_H


#include "engine/logging/Logger.h"

#include "game/entities/player/state/OnGroundState.h"

namespace game {

    class IdleState : public OnGroundState {
    public:
        IdleState() = default;

        ~IdleState() override = default;

        void enter(game::Player &player) override;

        void physicsUpdate(game::Player &player) override;

        void graphicsUpdate(game::Player &player) override;

        void handleInput(game::Player &player, const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_IDLESTATE_H
