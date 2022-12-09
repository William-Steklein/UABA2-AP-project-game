#include "IdleState.h"
#include "RunState.h"
#include "CrouchState.h"

namespace game {
    void IdleState::enter(Player &player) {
        player._animated_sprite->start("idle", true, player.isFacingLeft());
    }

    void IdleState::physicsUpdate(game::Player &player) {
        OnGroundState::physicsUpdate(player);
    }

    void IdleState::graphicsUpdate(Player &player) {

    }

    void IdleState::handleInput(Player &player, const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::LEFT:
            case InputEvent::Type::RIGHT:
                if (input.state_enter) {
                    player.setState(std::make_shared<RunState>());
                }

                break;

            case InputEvent::Type::DOWN:
                if (input.state_enter) {
                    player.setState(std::make_shared<CrouchState>());
                }

            default:
                break;
        }

        game::OnGroundState::handleInput(player, input);
    }
} // game