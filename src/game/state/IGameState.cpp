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

        for (auto entity_it = _weak_entities.begin(); entity_it != _weak_entities.end();) {
            if ((*entity_it).expired()) {
                entity_it = _weak_entities.erase(entity_it);
            } else {
                entity_it->lock()->graphicsUpdate(t, dt);

                entity_it++;
            }
        }
    }

    void IGameState::physicsUpdate(double t, float dt) {
        for (const auto &entity: _entities) {
            entity->physicsUpdate(t, dt);
        }

        for (auto entity_it = _weak_entities.begin(); entity_it != _weak_entities.end();) {
            if ((*entity_it).expired()) {
                entity_it = _weak_entities.erase(entity_it);
            } else {
                entity_it->lock()->physicsUpdate(t, dt);

                entity_it++;
            }
        }
    }
} // game