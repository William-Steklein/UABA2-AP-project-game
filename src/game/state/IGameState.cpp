#include "IGameState.h"

namespace game {
    void IGameState::reset(Game &game) {
        _entities.clear();
        _physics_entities.clear();

        enter(game);
    }

    void IGameState::update(Game &game, double t, float dt) {
        for (const auto &entity : _entities) {
            entity->update(t, dt);
        }
    }

    void IGameState::physicsUpdate(Game &game, double t, float dt) {
        for (const auto &entity : _physics_entities) {
            entity->update(t, dt);
        }
    }
} // game