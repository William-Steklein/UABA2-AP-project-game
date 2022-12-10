#ifndef GAME_ENGINE_WALLSLIDESTATE_H
#define GAME_ENGINE_WALLSLIDESTATE_H


#include "IPlayerState.h"

namespace game {

    class WallSlideState : public IPlayerState {
    public:
        WallSlideState() = default;

        ~WallSlideState() override = default;

        void enter(Player &player) override;

        void physicsUpdate(game::Player &player) override;

        void handleInput(Player &player, const InputEvent &input) override;
    };

}

#endif //GAME_ENGINE_WALLSLIDESTATE_H
