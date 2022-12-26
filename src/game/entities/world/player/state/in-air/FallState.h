#ifndef GAME_ENGINE_FALLSTATE_H
#define GAME_ENGINE_FALLSTATE_H


#include "InAirState.h"

namespace game {

    class FallState : public InAirState {
    public:
        using InAirState::InAirState;

        ~FallState() override = default;

        void enter() override;
    };

} // game

#endif //GAME_ENGINE_FALLSTATE_H
