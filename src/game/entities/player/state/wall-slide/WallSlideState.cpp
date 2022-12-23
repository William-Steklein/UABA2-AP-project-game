#include "WallSlideState.h"
#include "game/entities/player/state/in-air/FallState.h"
#include "game/entities/player/state/on-ground/IdleState.h"
#include "game/entities/player/state/in-air/JumpState.h"

namespace game {
    void WallSlideState::enter() {
        // reverse direction
        _player.updateDirection(_player.isFacingLeft() ? Player::Direction::RIGHT : Player::Direction::LEFT);

        _player._animated_sprite->start("wall_slide", true, _player.isFacingLeft());

        _player._physics_component->setVelocity({0, 0});
        _player._physics_component->setWallVelocityClamp(true);
    }

    void WallSlideState::exit() {
        _player._physics_component->setWallVelocityClamp(false);
    }

    void WallSlideState::physicsUpdate() {
        _player._physics_component->applyGravityForce(0.25f);

        if ((!_player.isFacingLeft() && !_player._left_wall_slide_ray->collided()) ||
            (_player.isFacingLeft() && !_player._right_wall_slide_ray->collided())) {
            _player.setState(std::make_shared<FallState>(_player));
        }

        if (_player._standing_ray->collided()) {
            _player.setState(std::make_shared<IdleState>(_player));
        }

        IPlayerState::physicsUpdate();
    }

    void WallSlideState::handleInput(const InputEvent &input) {
        if ((input.type == InputEvent::Type::LEFT && _player.isFacingLeft()) ||
            (input.type == InputEvent::Type::RIGHT && !_player.isFacingLeft())) {
            _player.setState(std::make_shared<FallState>(_player));
        }

        if (input.type == InputEvent::Type::JUMP) {
            if (input.state == InputEvent::State::ENTERED) {
                _player._physics_component->setVelocity({0, 0});
                _player.setState(std::make_shared<WallJumpState>(_player));
            }
        }

//        IPlayerState::handleInput(player, input);
    }
}