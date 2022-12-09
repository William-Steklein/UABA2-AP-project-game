#include "OnGroundState.h"
#include "FallState.h"
#include "JumpState.h"

namespace game {
    void OnGroundState::physicsUpdate(game::Player &player) {
        if (!player._standing_ray->collided()) {
            player.setState(std::make_shared<FallState>());
        }

        IPlayerState::physicsUpdate(player);
    }

    void OnGroundState::handleInput(Player &player, const InputEvent &input) {
        if (input.state_enter) {
            switch (input.type) {
                case InputEvent::Type::JUMP:
                    player.setState(std::make_shared<JumpState>());

                    break;

                default:
                    break;
            }
        }

        IPlayerState::handleInput(player, input);
    }
} // game