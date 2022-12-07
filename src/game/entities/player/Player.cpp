#include "Player.h"
#include "game/entities/player/IdleState.h"

namespace game {
    Player::Player(engine::Transform transform,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite,
                   std::shared_ptr<engine::IShapeComponent> rectangle)
            : engine::Entity(std::move(transform)),
              _animated_sprite(std::move(animated_sprite)),
              _physics_component(std::make_shared<engine::PhysicsComponent>(false)),
              _rectangle(std::move(rectangle)) {
        addComponents({_animated_sprite, _rectangle}, false);
        addComponent(_physics_component, true);

        engine::Vector2f hit_box_size = _animated_sprite->getSize();
        hit_box_size.x = hit_box_size.x * 0.5f;
        hit_box_size.y = hit_box_size.y * 0.8f;

        std::shared_ptr<engine::HitBox> hit_box = std::make_shared<engine::HitBox>(hit_box_size);
        addComponent(hit_box);
        _physics_component->setHitBox(hit_box);

        _standing_ray = std::make_shared<engine::Ray>(engine::Ray(
                {-hit_box->getSize().x / 2, -hit_box->getSize().y / 2},
                {hit_box->getSize().x / 2, -hit_box->getSize().y / 2}
        ));
        addComponent(_standing_ray, true);

        _rectangle->setSize(hit_box_size);
        _rectangle->setFillcolor({255, 0, 255, 100});
//        _rectangle->setRelativeTransform({{0, -0.05}, {1, 1}, 0});

        _state = std::make_shared<IdleState>();
        _state->enter(*this);
    }

    void Player::graphicsUpdate(double t, float dt) {
        _state->update(*this);

        Entity::graphicsUpdate(t, dt);
    }

    void Player::handleInput(const InputEvent &input) {
        std::shared_ptr<IPlayerState> state = _state->handleInput(*this, input);

        if (state != nullptr) {
            _state = state;
            _state->enter(*this);
        }
    }
} // game