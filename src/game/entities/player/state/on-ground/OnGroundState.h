#ifndef GAME_ENGINE_ONGROUNDSTATE_H
#define GAME_ENGINE_ONGROUNDSTATE_H


#include "game/entities/player/state/IPlayerState.h"

namespace game {

    class OnGroundState : public IPlayerState {
    public:
        ~OnGroundState() override = default;

        void physicsUpdate() override;

        void handleInput(const InputEvent &input) override;

//    protected:
        OnGroundState(Player &player);
    };

} // game

#endif //GAME_ENGINE_ONGROUNDSTATE_H
