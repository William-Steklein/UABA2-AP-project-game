#ifndef GAME_ENGINE_ONGROUNDSTATE_H
#define GAME_ENGINE_ONGROUNDSTATE_H


#include "IPlayerState.h"

namespace game {

    class OnGroundState : public IPlayerState {
    public:
        ~OnGroundState() override = default;

        void physicsUpdate(game::Player &player) override;

        void handleInput(Player &player, const InputEvent &input) override;

    protected:
        OnGroundState() = default;
    };

} // game

#endif //GAME_ENGINE_ONGROUNDSTATE_H
