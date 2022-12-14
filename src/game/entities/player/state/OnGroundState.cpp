#include "OnGroundState.h"
#include "FallState.h"
#include "JumpState.h"
#include "CrouchState.h"

namespace game {
    void OnGroundState::physicsUpdate(game::Player &player) {
        if (!player._standing_ray->collided()) {
            player.setState(std::make_shared<FallState>());
        }

        IPlayerState::physicsUpdate(player);
    }

    void OnGroundState::handleInput(Player &player, const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::JUMP:
                player.setState(std::make_shared<JumpState>());

                break;

            case InputEvent::Type::DOWN:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    player.setState(std::make_shared<CrouchState>());
                }

            default:
                break;
        }

        IPlayerState::handleInput(player, input);
    }
} // game