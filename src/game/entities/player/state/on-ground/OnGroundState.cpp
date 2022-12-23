#include "OnGroundState.h"
#include "game/entities/player/state/in-air/FallState.h"
#include "game/entities/player/state/in-air/JumpState.h"
#include "CrouchState.h"

namespace game {
    void OnGroundState::physicsUpdate(double t, float dt) {
        if (!_state_machine._standing_ray->collided()) {
            set<FallState>();
        }

        IPlayerState::physicsUpdate(0, 0);
    }

    void OnGroundState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::JUMP:
                set<JumpState>();

                break;

            case InputEvent::Type::DOWN:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    set<CrouchState>();
                }

            default:
                break;
        }

        IPlayerState::handleInput(input);
    }
} // game