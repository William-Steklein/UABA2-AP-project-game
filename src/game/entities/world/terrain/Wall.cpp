#include "Wall.h"

namespace game {
    Wall::Wall(engine::Transform transform, std::shared_ptr<engine::ISpriteComponent> sprite)
            : engine::Entity(std::move(transform)), _sprite(std::move(sprite)) {
        _physics_component = std::make_shared<engine::PhysicsComponent>(true);
        addComponents({_sprite, _physics_component});

        std::shared_ptr<engine::HitBox> hit_box = std::make_shared<engine::HitBox>(_sprite->getSize());
        addComponent(hit_box);
        _physics_component->setHitBox(hit_box);
    }

    std::shared_ptr<engine::PhysicsComponent> Wall::getPhysicsComponent() {
        return _physics_component;
    }
} // game