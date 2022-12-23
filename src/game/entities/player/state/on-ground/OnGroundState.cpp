#include "OnGroundState.h"
#include "game/entities/player/state/in-air/FallState.h"
#include "game/entities/player/state/in-air/JumpState.h"
#include "CrouchState.h"

namespace game {
    void OnGroundState::physicsUpdate() {
        if (!_player._standing_ray->collided()) {
            _player.setState(std::make_shared<FallState>(_player));
        }

        IPlayerState::physicsUpdate();
    }

    void OnGroundState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::JUMP:
                _player.setState(std::make_shared<JumpState>(_player));

                break;

            case InputEvent::Type::DOWN:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    _player.setState(std::make_shared<CrouchState>(_player));
                }

            default:
                break;
        }

        IPlayerState::handleInput(input);
    }

    OnGroundState::OnGroundState(Player &player) : IPlayerState(player) {}
} // game