#include "IGameState.h"

namespace game {
    IGameState::IGameState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : engine::PushdownState<Game, IGameState, InputEvent>(state_machine, states) {

    }

    void IGameState::reset() {
        _entities.clear();

        enter();
    }

    void IGameState::graphicsUpdate(double t, float dt) {
        for (const auto &entity: _entities) {
            entity->graphicsUpdate(t, dt);
        }
    }

    void IGameState::physicsUpdate(double t, float dt) {
        for (const auto &entity: _entities) {
            entity->physicsUpdate(t, dt);
        }
    }
} // game