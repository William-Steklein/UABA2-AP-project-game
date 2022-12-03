#include "Player.h"
#include "game/entities/player/IdleState.h"

namespace game {
    Player::Player(engine::Transform transform,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite)
            : engine::Entity(std::move(transform)),
              _animated_sprite(std::move(animated_sprite)),
              _physics_component(std::make_shared<engine::PhysicsComponent>(false)) {
        addComponent(_animated_sprite, false);
        addComponent(_physics_component, true);

        _physics_component->getHitBox()->setPosition(getPosition());
        _physics_component->getHitBox()->setSize(_animated_sprite->getSize());

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