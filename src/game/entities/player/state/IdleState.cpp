#include "IdleState.h"
#include "RunState.h"
#include "CrouchState.h"

namespace game {
    void IdleState::enter(Player &player) {
        player._animated_sprite->start("idle", true, player.isFacingLeft());
        player._physics_component->setVelocity({0, 0});
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
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    player.setState(std::make_shared<RunState>());
                }

                break;

            case InputEvent::Type::DOWN:
                if (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE) {
                    player.setState(std::make_shared<CrouchState>());
                }

            default:
                break;
        }

        game::OnGroundState::handleInput(player, input);
    }
} // game