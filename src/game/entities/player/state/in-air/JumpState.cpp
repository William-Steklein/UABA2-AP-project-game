#include "JumpState.h"
#include "FallState.h"

namespace game {
    void JumpState::enter() {
        _player._animated_sprite->start("jump", false, _player.isFacingLeft());

        _player._physics_component->jump(_player.isFacingLeft());
        _player._standing_ray->reset();
    }

    void JumpState::physicsUpdate() {
        if (_player._physics_component->getVelocity().y <= 0) {
            _player.setState(std::make_shared<FallState>(_player));
        }

        InAirState::physicsUpdate();
    }

    void WallJumpState::enter() {
        _player._animated_sprite->start("jump", false, _player.isFacingLeft());

        _player._physics_component->walljump(_player.isFacingLeft());
        _player._standing_ray->reset();
    }
} // game