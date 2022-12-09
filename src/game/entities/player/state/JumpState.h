#ifndef GAME_ENGINE_JUMPSTATE_H
#define GAME_ENGINE_JUMPSTATE_H


#include "InAirState.h"

namespace game {

    class JumpState : public InAirState {
    public:
        JumpState() = default;

        ~JumpState() override = default;

        void physicsUpdate(game::Player &player) override;

        void enter(Player &player) override;
    };

} // game

#endif //GAME_ENGINE_JUMPSTATE_H
