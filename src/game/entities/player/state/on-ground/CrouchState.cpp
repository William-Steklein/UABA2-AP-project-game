#include "CrouchState.h"
#include "IdleState.h"

namespace game {
    void CrouchState::enter() {
        _player._animated_sprite->start("crouch", true, _player.isFacingLeft());
    }

    void CrouchState::physicsUpdate() {
        _player._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate();
    }

    void CrouchState::handleInput(const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED && input.type == InputEvent::Type::DOWN) {
            _player.setState(std::make_shared<IdleState>(_player));
        }

        OnGroundState::handleInput(input);
    }
} // game