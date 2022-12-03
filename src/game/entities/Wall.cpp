#include "Wall.h"

namespace game {
    Wall::Wall(engine::Transform transform, std::shared_ptr<engine::ISpriteComponent> sprite)
    : engine::Entity(transform) {
        _physics_component = std::make_shared<engine::PhysicsComponent>(true);
        addComponents({sprite, _physics_component});
    }
} // game