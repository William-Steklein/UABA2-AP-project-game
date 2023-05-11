#ifndef GAME_ENGINE_IPLAYERSTATE_H
#define GAME_ENGINE_IPLAYERSTATE_H

#include <memory>

#include "engine/state-machine/FiniteState.h"

#include "game/entities/world/player/Player.h"

namespace game {
    class IPlayerState : public engine::FiniteState<Player, IPlayerState, InputEvent> {
    public:
        IPlayerState(Player &state_machine, std::unique_ptr<IPlayerState> &state);

        void physicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;
    };

} // game

#endif //GAME_ENGINE_IPLAYERSTATE_H
