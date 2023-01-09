#include "WallSlideState.h"
#include "game/entities/world/player/state/in-air/FallState.h"
#include "game/entities/world/player/state/on-ground/IdleState.h"
#include "game/entities/world/player/state/in-air/JumpState.h"

namespace game {
    void WallSlideState::enter() {
        // reverse direction
        _state_machine.updateDirection(_state_machine.isFacingLeft() ? Player::Direction::RIGHT : Player::Direction::LEFT);

        _state_machine._animated_sprite->start("wall_slide", true, _state_machine.isFacingLeft(), false);

        _state_machine._physics_component->setWallVelocityClamp(true);
    }

    void WallSlideState::exit() {
        _state_machine._physics_component->setWallVelocityClamp(false);
    }

    void WallSlideState::physicsUpdate(double t, float dt) {
        _state_machine._physics_component->applyGravityForce(0.25f);

        _state_machine._physics_component->applyWallSlidingFrictionForce();

        if ((!_state_machine.isFacingLeft() && !_state_machine._left_wall_slide_ray->collided()) ||
            (_state_machine.isFacingLeft() && !_state_machine._right_wall_slide_ray->collided())) {
            return set<FallState>();
        }

        if (_state_machine._standing_ray->collided()) {
            return set<IdleState>();
        }

        IPlayerState::physicsUpdate(t, dt);
    }

    void WallSlideState::handleInput(const InputEvent &input) {
        if ((input.type == InputEvent::Type::LEFT && _state_machine.isFacingLeft()) ||
            (input.type == InputEvent::Type::RIGHT && !_state_machine.isFacingLeft())) {
//            _changeable = false;
            return set<FallState>();
        }

        if (input.type == InputEvent::Type::JUMP) {
            if (input.state == InputEvent::State::ENTERED) {
                _state_machine._physics_component->setVelocity({0, 0});
//                _changeable = false;
                return set<WallJumpState>();
            }
        }
    }
}