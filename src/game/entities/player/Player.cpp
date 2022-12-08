#include "Player.h"
#include "game/entities/player/IdleState.h"

namespace game {
    Player::Player(engine::Transform transform,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite)
            : engine::Entity(std::move(transform)),
              _animated_sprite(std::move(animated_sprite)),
              _physics_component(std::make_shared<engine::PhysicsComponent>(false)) {
        addComponents({_animated_sprite}, false);
        addComponent(_physics_component, true);

        engine::Vector2f hit_box_size = _animated_sprite->getSize();
        hit_box_size.x = hit_box_size.x * 0.3f;
        hit_box_size.y = hit_box_size.y * 0.8f;

        float hit_box_y_offset = -hit_box_size.y * 0.09f;

        std::shared_ptr<engine::HitBox> hit_box = std::make_shared<engine::HitBox>(hit_box_size);
        hit_box->setRelativeTransform({{0, hit_box_y_offset}, {1, 1}, 0});
        addComponent(hit_box);
        _physics_component->setHitBox(hit_box);

        _standing_ray = std::make_shared<engine::Ray>(engine::Ray(
                {(-hit_box->getSize().x / 2) * 0.99f,
                 hit_box->getRelativeTransform().position.y + (-hit_box->getSize().y / 2) * 1.01f},
                {(hit_box->getSize().x / 2) * 0.99f,
                 hit_box->getRelativeTransform().position.y + (-hit_box->getSize().y / 2) * 1.01f}
        ));
        addComponent(_standing_ray, true);

        _left_wall_slide_ray = std::make_shared<engine::Ray>(engine::Ray(
                {(-hit_box->getSize().x / 2) * 1.01f,
                 hit_box->getRelativeTransform().position.y + (-hit_box->getSize().y / 2) * 0.99f},
                {(-hit_box->getSize().x / 2) * 1.01f,
                 hit_box->getRelativeTransform().position.y + (hit_box->getSize().y / 2) * 0.99f}
        ));
        addComponent(_left_wall_slide_ray, true);

        _right_wall_slide_ray = std::make_shared<engine::Ray>(engine::Ray(
                {(hit_box->getSize().x / 2) * 1.01f,
                 hit_box->getRelativeTransform().position.y + (-hit_box->getSize().y / 2) * 0.99f},
                {(hit_box->getSize().x / 2) * 1.01f,
                 hit_box->getRelativeTransform().position.y + (hit_box->getSize().y / 2) * 0.99f}
        ));
        addComponent(_right_wall_slide_ray, true);

        _state = std::make_shared<IdleState>();
        _state->enter(*this);
    }

    void Player::physicsUpdate(double t, float dt) {
        if (_standing_ray->isCollided()) {
            _standing_ray->reset();

            LOGDEBUG("standing ray collision!");
        }

        if (_left_wall_slide_ray->isCollided()) {
            _left_wall_slide_ray->reset();

            LOGDEBUG("left wall slide ray collision!");
        }

        if (_right_wall_slide_ray->isCollided()) {
            _right_wall_slide_ray->reset();

            LOGDEBUG("right wall slide ray collision!");
        }

        engine::Entity::physicsUpdate(t, dt);
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