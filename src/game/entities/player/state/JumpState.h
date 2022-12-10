#ifndef GAME_ENGINE_JUMPSTATE_H
#define GAME_ENGINE_JUMPSTATE_H


#include "InAirState.h"

namespace game {

    class JumpState : public InAirState {
    public:
        JumpState(bool wall_jump = false);

        ~JumpState() override = default;

        void enter(Player &player) override;

        void physicsUpdate(game::Player &player) override;

    private:
        bool _wall_jump;
    };

} // game

#endif //GAME_ENGINE_JUMPSTATE_H
