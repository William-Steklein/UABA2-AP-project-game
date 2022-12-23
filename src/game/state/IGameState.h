#ifndef GAME_ENGINE_IGAMESTATE_H
#define GAME_ENGINE_IGAMESTATE_H

#include <set>

#include <engine/state-machine/PushdownState.h>
#include <engine/entity/Entity.h>

#include "game/Game.h"
#include "game/input/InputEvent.h"

namespace game {
    class IGameState : public engine::PushdownState<Game, IGameState, InputEvent> {
    public:
        IGameState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        void enter() override;

        void reset() override;

        void graphicsUpdate(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

    protected:
        std::set<std::shared_ptr<engine::Entity>> _entities;
    };

} // game

#endif //GAME_ENGINE_IGAMESTATE_H
