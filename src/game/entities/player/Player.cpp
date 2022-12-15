#include "Player.h"
#include "game/entities/player/state/IdleState.h"

namespace game {
    Player::Player(engine::Transform transform,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite)
            : engine::Entity(std::move(transform)),
              _animated_sprite(std::move(animated_sprite)),
              _physics_component(std::make_shared<PlayerPhysicsComponent>()) {
        addComponents({_animated_sprite}, false);
        addComponent(_physics_component, true);

        createHitBoxAndRays();

        _state = std::make_shared<IdleState>();
        _state->enter(*this);
    }

    void Player::setState(std::shared_ptr<IPlayerState> state) {
        if (state != nullptr) {
            _state->exit(*this);
            _state = std::move(state);
            _state->enter(*this);
        }
    }

    void Player::physicsUpdate(double t, float dt) {
        _state->physicsUpdate(*this);

        if (_standing_ray->collided()) {
            _standing_ray->reset();
        }

        if (_left_wall_slide_ray->collided()) {
            _left_wall_slide_ray->reset();
        }

        if (_right_wall_slide_ray->collided()) {
            _right_wall_slide_ray->reset();
        }

        engine::Entity::physicsUpdate(t, dt);
    }

    void Player::graphicsUpdate(double t, float dt) {
        _state->graphicsUpdate(*this);

        Entity::graphicsUpdate(t, dt);
    }

    void Player::handleInput(const InputEvent &input) {
        _state->handleInput(*this, input);
    }

    void Player::createHitBoxAndRays() {
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
    }

    void Player::updateDirection(Player::Direction direction) {
        _direction = direction;
        _animated_sprite->setMirrorH(_direction == Direction::LEFT);
    }

    bool Player::isFacingLeft() {
        return _direction == Direction::LEFT;
    }
} // game