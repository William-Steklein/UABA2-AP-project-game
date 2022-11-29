#include "IGameState.h"

namespace game {
    std::shared_ptr<IGameState> IGameState::update(Game &game, double t, float dt) {
        for (const auto &entity : _entities) {
            entity->update(t, dt);
        }
        return nullptr;
    }

    std::shared_ptr<IGameState> IGameState::physicsUpdate(Game &game, double t, float dt) {
        for (const auto &entity : _physics_entities) {
            entity->update(t, dt);
        }
        return nullptr;
    }
} // game