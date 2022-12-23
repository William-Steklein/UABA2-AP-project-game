#include "IdleState.h"
#include "RunState.h"

namespace game {
    void IdleState::enter() {
        _player._animated_sprite->start("idle", true, _player.isFacingLeft());
    }

    void IdleState::physicsUpdate() {
        _player._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate();
    }

    void IdleState::graphicsUpdate() {

    }

    void IdleState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::LEFT:
            case InputEvent::Type::RIGHT:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    _player.setState(std::make_shared<RunState>(_player));
                }

                break;

            default:
                break;
        }

        game::OnGroundState::handleInput(input);
    }
} // game