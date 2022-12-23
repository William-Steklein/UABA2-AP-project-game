#ifndef GAME_ENGINE_CROUCHSTATE_H
#define GAME_ENGINE_CROUCHSTATE_H


#include "OnGroundState.h"

namespace game {

    class CrouchState : public OnGroundState {
    public:
        using OnGroundState::OnGroundState;

        ~CrouchState() override = default;

        void enter() override;

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_CROUCHSTATE_H
