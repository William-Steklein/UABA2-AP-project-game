#include "Wall.h"

namespace game {
    Wall::Wall(engine::Transform transform, const engine::Vector2f &size)
            : engine::Entity(std::move(transform)) {
        _physics_component = std::make_shared<engine::PhysicsComponent>(true);
        addComponent(_physics_component);

        std::shared_ptr<engine::HitBox> hit_box = std::make_shared<engine::HitBox>(size);
        addComponent(hit_box);
        _physics_component->setHitBox(hit_box);
    }

    std::shared_ptr<engine::PhysicsComponent> Wall::getPhysicsComponent() {
        return _physics_component;
    }
} // game