#include "IdleState.h"
#include "RunState.h"

namespace game {
    void IdleState::enter() {
        _state_machine._animated_sprite->start("idle", true, _state_machine.isFacingLeft(), false);
    }

    void IdleState::physicsUpdate(double t, float dt) {
        _state_machine._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate(0, 0);
    }

    void IdleState::graphicsUpdate(double t, float dt) {

    }

    void IdleState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::LEFT:
            case InputEvent::Type::RIGHT:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    set<RunState>();
                }

                break;

            default:
                break;
        }

        game::OnGroundState::handleInput(input);
    }
} // game