#ifndef GAME_ENGINE_FALLSTATE_H
#define GAME_ENGINE_FALLSTATE_H


#include "InAirState.h"

namespace game {

    class FallState : public InAirState {
    public:
        FallState() = default;

        ~FallState() override = default;

        void enter(Player &player) override;
    };

} // game

#endif //GAME_ENGINE_FALLSTATE_H
