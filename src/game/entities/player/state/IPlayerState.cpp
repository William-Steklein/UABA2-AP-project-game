#include "IPlayerState.h"

namespace game {

    IPlayerState::IPlayerState(Player &state_machine, std::unique_ptr<IPlayerState> &state)
            : engine::FiniteState<Player, IPlayerState, InputEvent>(state_machine, state) {

    }

    void IPlayerState::handleInput(const InputEvent &input) {
        if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
            switch (input.type) {
                case InputEvent::Type::LEFT:
                    _state_machine.updateDirection(Player::Direction::LEFT);
                    break;

                case InputEvent::Type::RIGHT:
                    _state_machine.updateDirection(Player::Direction::RIGHT);
                    break;

                default:
                    break;
            }
        }
    }

} // namespace game