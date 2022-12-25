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
        }

        InAirState::physicsUpdate(0, 0);
    }

    void WallJumpState::enter() {
        _state_machine._animated_sprite->start("jump", false, _state_machine.isFacingLeft(), false);

        _state_machine._physics_component->walljump(_state_machine.isFacingLeft());
        _state_machine._standing_ray->reset();
    }
} // game