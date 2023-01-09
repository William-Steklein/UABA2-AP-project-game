#include "JumpState.h"
#include "FallState.h"

namespace game {
    void JumpState::enter() {
        _state_machine._animated_sprite->start("jump", false, _state_machine.isFacingLeft(), false);

        _state_machine._physics_component->jump(_state_machine.isFacingLeft());
        _state_machine._standing_ray->reset();
    }

    void JumpState::physicsUpdate(double t, float dt) {
        if (_state_machine._physics_component->getVelocity().y <= 0) {
            set<FallState>();

            return;
        }

        InAirState::physicsUpdate(t, dt);
    }

    void WallJumpState::enter() {
        _state_machine._animated_sprite->start("jump", false, _state_machine.isFacingLeft(), false);

        _state_machine._physics_component->walljump(_state_machine.isFacingLeft());
        _state_machine._standing_ray->reset();
        _state_machine._right_wall_slide_ray->reset();
        _state_machine._left_wall_slide_ray->reset();
    }
} // game