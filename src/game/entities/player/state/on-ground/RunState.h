#ifndef GAME_ENGINE_RUNSTATE_H
#define GAME_ENGINE_RUNSTATE_H


#include "OnGroundState.h"

namespace game {

    class RunState : public OnGroundState {
    public:
        using OnGroundState::OnGroundState;

        ~RunState() override = default;

        void enter() override;

        void physicsUpdate() override;

        void handleInput(const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_RUNSTATE_H
