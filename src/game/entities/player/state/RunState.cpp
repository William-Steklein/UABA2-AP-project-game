#include "RunState.h"
#include "IdleState.h"

namespace game {
    void RunState::enter(Player &player) {
        player._animated_sprite->start("run", true, player.isFacingLeft());
    }

    void RunState::physicsUpdate(Player &player) {
        // stopping friction when changing direction
        if (player.isFacingLeft() && player._physics_component->getVelocity().x > 0 ||
            !player.isFacingLeft() && player._physics_component->getVelocity().x < 0) {
            player._physics_component->applyStoppingFrictionForce();
        }

        player._physics_component->applyHorizontalMovementForce(player.isFacingLeft());


        OnGroundState::physicsUpdate(player);
    }

    void RunState::handleInput(Player &player, const InputEvent &input) {
        if (input.state == InputEvent::State::EXITED) {
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