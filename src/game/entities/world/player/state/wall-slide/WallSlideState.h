#ifndef GAME_ENGINE_WALLSLIDESTATE_H
#define GAME_ENGINE_WALLSLIDESTATE_H


#include "game/entities/world/player/state/IPlayerState.h"

namespace game {

    class WallSlideState : public IPlayerState {
    public:
        using IPlayerState::IPlayerState;

        ~WallSlideState() override = default;

        void enter() override;

        void exit() override;

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;
    };

}

#endif //GAME_ENGINE_WALLSLIDESTATE_H
