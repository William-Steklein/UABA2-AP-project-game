#ifndef GAME_ENGINE_INAIRSTATE_H
#define GAME_ENGINE_INAIRSTATE_H


#include "game/entities/world/player/state/IPlayerState.h"

namespace game {

    class InAirState : public IPlayerState {
    public:
        InAirState(Player &state_machine, std::unique_ptr<IPlayerState> &state);

        ~InAirState() override = default;

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;

    protected:
        bool _h_movement;
    };

} // game

#endif //GAME_ENGINE_INAIRSTATE_H
