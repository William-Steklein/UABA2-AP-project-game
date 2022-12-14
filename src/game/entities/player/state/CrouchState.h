#ifndef GAME_ENGINE_CROUCHSTATE_H
#define GAME_ENGINE_CROUCHSTATE_H


#include "game/entities/player/state/OnGroundState.h"

namespace game {

    class CrouchState : public OnGroundState {
    public:
        CrouchState() = default;

        ~CrouchState() override = default;

        void enter(game::Player &player) override;

        void physicsUpdate(game::Player &player) override;

        void handleInput(Player &player, const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_CROUCHSTATE_H
