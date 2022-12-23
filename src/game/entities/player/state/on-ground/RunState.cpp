#include "RunState.h"
#include "IdleState.h"

namespace game {
    void RunState::enter() {
        _state_machine._animated_sprite->start("run", true, _state_machine.isFacingLeft());
    }

    void RunState::physicsUpdate(double t, float dt) {
        // stopping friction when changing direction
        if (_state_machine.isFacingLeft() && _state_machine._physics_component->getVelocity().x > 0 ||
            !_state_machine.isFacingLeft() && _state_machine._physics_component->getVelocity().x < 0) {
            _state_machine._physics_component->applyStoppingFrictionForce();
        }

        _state_machine._physics_component->applyHorizontalMovementForce(_state_machine.isFacingLeft());


        OnGroundState::physicsUpdate(0, 0);
    }

    void RunState::handleInput(const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED) {
            if ((input.type == InputEvent::Type::LEFT && _state_machine.isFacingLeft()) ||
                (input.type == InputEvent::Type::RIGHT && !_state_machine.isFacingLeft())) {
                set<IdleState>();
            }
        }

        switch (input.type) {

            default:
                break;
        }


        OnGroundState::handleInput(input);
    }
} // game