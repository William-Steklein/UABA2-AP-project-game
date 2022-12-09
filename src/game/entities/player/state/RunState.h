#ifndef GAME_ENGINE_RUNSTATE_H
#define GAME_ENGINE_RUNSTATE_H


#include "game/entities/player/state/OnGroundState.h"

namespace game {

    class RunState : public OnGroundState {
    public:
        RunState() = default;

        ~RunState() override = default;

        void enter(game::Player &player) override;

        void physicsUpdate(game::Player &player) override;

        void handleInput(Player &player, const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_RUNSTATE_H
