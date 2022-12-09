#include "RunState.h"
#include "IdleState.h"

namespace game {
    void RunState::enter(Player &player) {
        player._animated_sprite->start("run", true, player.isFacingLeft());
    }

    void RunState::physicsUpdate(Player &player) {
        player._physics_component->applyHorizontalMovementForce(player.isFacingLeft());

        OnGroundState::physicsUpdate(player);
    }

    void RunState::handleInput(Player &player, const InputEvent &input) {
        if (!input.state_enter) {
            if ((input.type == InputEvent::Type::LEFT && player.isFacingLeft()) ||
                (input.type == InputEvent::Type::RIGHT && !player.isFacingLeft())) {
                player.setState(std::make_shared<IdleState>());
            }
        }

        switch (input.type) {

            default:
                break;
        }


        OnGroundState::handleInput(player, input);
    }
} // game