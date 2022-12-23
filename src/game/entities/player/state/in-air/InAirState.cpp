#include "InAirState.h"
#include "game/entities/player/state/on-ground/IdleState.h"
#include "game/entities/player/state/wall-slide/WallSlideState.h"

namespace game {
    void InAirState::physicsUpdate() {
        // gravity
        _player._physics_component->applyGravityForce();

        // air movement
        if (_h_movement) {
            _player._physics_component->applyHorizontalMovementForce(_player.isFacingLeft());
        }

        // wall slide
        if (_player.isFacingLeft() && _player._left_wall_slide_ray->collided() ||
            !_player.isFacingLeft() && _player._right_wall_slide_ray->collided()) {
            _player.setState(std::make_shared<WallSlideState>(_player));
        }

        // standing
        if (_player._standing_ray->collided()) {
            _player.setState(std::make_shared<IdleState>(_player));
        }

        IPlayerState::physicsUpdate();
    }

    void InAirState::handleInput(const InputEvent &input) {
        if (input.type == InputEvent::Type::LEFT || input.type == InputEvent::Type::RIGHT) {
            _h_movement = (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE);
        }

        IPlayerState::handleInput(input);
    }

    InAirState::InAirState(Player &player) : IPlayerState(player), _h_movement(false) {

    }
} // game