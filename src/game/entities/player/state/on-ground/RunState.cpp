#include "RunState.h"
#include "IdleState.h"

namespace game {
    void RunState::enter() {
        _player._animated_sprite->start("run", true, _player.isFacingLeft());
    }

    void RunState::physicsUpdate() {
        // stopping friction when changing direction
        if (_player.isFacingLeft() && _player._physics_component->getVelocity().x > 0 ||
            !_player.isFacingLeft() && _player._physics_component->getVelocity().x < 0) {
            _player._physics_component->applyStoppingFrictionForce();
        }

        _player._physics_component->applyHorizontalMovementForce(_player.isFacingLeft());


        OnGroundState::physicsUpdate();
    }

    void RunState::handleInput(const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED) {
            if ((input.type == InputEvent::Type::LEFT && _player.isFacingLeft()) ||
                (input.type == InputEvent::Type::RIGHT && !_player.isFacingLeft())) {
                _player.setState(std::make_shared<IdleState>(_player));
            }
        }

        switch (input.type) {

            default:
                break;
        }


        OnGroundState::handleInput(input);
    }
} // game