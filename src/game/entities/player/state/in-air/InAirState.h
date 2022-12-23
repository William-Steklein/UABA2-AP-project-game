#ifndef GAME_ENGINE_INAIRSTATE_H
#define GAME_ENGINE_INAIRSTATE_H


#include "game/entities/player/state/IPlayerState.h"

namespace game {

    class InAirState : public IPlayerState {
    public:
        ~InAirState() override = default;

        void physicsUpdate() override;

        void handleInput(const InputEvent &input) override;

//    protected:
        bool _h_movement;

        InAirState(Player &player);
    };

} // game

#endif //GAME_ENGINE_INAIRSTATE_H
