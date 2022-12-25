#include "CrouchState.h"
#include "IdleState.h"

namespace game {
    void CrouchState::enter() {
        _state_machine._animated_sprite->start("crouch", true, _state_machine.isFacingLeft(), false);
    }

    void CrouchState::physicsUpdate(double t, float dt) {
        _state_machine._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate(0, 0);
    }

    void CrouchState::handleInput(const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED && input.type == InputEvent::Type::DOWN) {
            set<IdleState>();
        }

        OnGroundState::handleInput(input);
    }
} // game