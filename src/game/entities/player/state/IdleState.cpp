#include "IdleState.h"
#include "RunState.h"

namespace game {
    void IdleState::enter(Player &player) {
        player._animated_sprite->start("idle", true, player.isFacingLeft());
    }

    void IdleState::physicsUpdate(game::Player &player) {
        player._physics_component->applyStoppingFrictionForce();

        OnGroundState::physicsUpdate(player);
    }

    void IdleState::graphicsUpdate(Player &player) {

    }

    void IdleState::handleInput(Player &player, const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::LEFT:
            case InputEvent::Type::RIGHT:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    player.setState(std::make_shared<RunState>());
                }

                break;

            default:
                break;
        }

        game::OnGroundState::handleInput(player, input);
    }
} // game