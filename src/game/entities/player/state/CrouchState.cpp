#include "CrouchState.h"
#include "IdleState.h"

namespace game {
    void CrouchState::enter(Player &player) {
        player._animated_sprite->start("crouch", true, player.isFacingLeft());
    }

    void CrouchState::physicsUpdate(Player &player) {
        player._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate(player);
    }

    void CrouchState::handleInput(Player &player, const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED && input.type == InputEvent::Type::DOWN) {
            player.setState(std::make_shared<IdleState>());
        }

        OnGroundState::handleInput(player, input);
    }
} // game