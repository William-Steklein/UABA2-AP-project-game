#include "Player.h"

namespace game {
    Player::Player(engine::Transform transform, std::shared_ptr<IPlayerState> state,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite)
            : engine::Entity(std::move(transform)),
            _state(std::move(state)),
            _animated_sprite(std::move(animated_sprite)),
            _physicsComponent(std::make_shared<engine::PhysicsComponent>(false)) {
        addComponents({_animated_sprite, _physicsComponent});

        _physicsComponent->getHitBox()->setPosition(getPosition());
        _physicsComponent->getHitBox()->setSize(_animated_sprite->getSize());

        _state->enter(*this);
    }

    void Player::update(double t, float dt) {
        _state->update(*this);

        Entity::update(t, dt);
    }

    void Player::handleInput(const InputEvent &input) {
        std::shared_ptr<IPlayerState> state = _state->handleInput(*this, input);

        if (state != nullptr) {
            _state = state;
            _state->enter(*this);
        }
    }
} // game