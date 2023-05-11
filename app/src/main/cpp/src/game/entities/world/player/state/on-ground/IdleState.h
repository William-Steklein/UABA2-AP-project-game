#ifndef GAME_ENGINE_IDLESTATE_H
#define GAME_ENGINE_IDLESTATE_H


#include "engine/logging/Logger.h"

#include "OnGroundState.h"

namespace game {

    class IdleState : public OnGroundState {
    public:
        using OnGroundState::OnGroundState;

        ~IdleState() override = default;

        void enter() override;

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_IDLESTATE_H
