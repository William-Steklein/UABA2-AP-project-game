#ifndef GAME_ENGINE_INAIRSTATE_H
#define GAME_ENGINE_INAIRSTATE_H


#include "IPlayerState.h"

namespace game {

    class InAirState : public IPlayerState {
    public:
        ~InAirState() override = default;

        void physicsUpdate(game::Player &player) override;

        void handleInput(Player &player, const InputEvent &input) override;

    protected:
        bool _h_movement;

        InAirState();
    };

} // game

#endif //GAME_ENGINE_INAIRSTATE_H
