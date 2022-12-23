#ifndef GAME_ENGINE_JUMPSTATE_H
#define GAME_ENGINE_JUMPSTATE_H


#include "InAirState.h"

namespace game {

    class JumpState : public InAirState {
    public:
        using InAirState::InAirState;

        void enter() override;

        void physicsUpdate(double t, float dt) override;
    };

    class WallJumpState : public JumpState {
    public:
        using JumpState::JumpState;

        void enter() override;
    };

} // game

#endif //GAME_ENGINE_JUMPSTATE_H
