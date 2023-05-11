#ifndef GAME_ENGINE_ONGROUNDSTATE_H
#define GAME_ENGINE_ONGROUNDSTATE_H


#include "game/entities/world/player/state/IPlayerState.h"

namespace game {

    class OnGroundState : public IPlayerState {
    public:
        using IPlayerState::IPlayerState;

        ~OnGroundState() override = default;

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_ONGROUNDSTATE_H
