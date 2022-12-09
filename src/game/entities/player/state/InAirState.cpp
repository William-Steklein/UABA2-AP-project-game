#include "InAirState.h"
#include "IdleState.h"

namespace game {
    void InAirState::physicsUpdate(Player &player) {
        // TODO: wall slide stuff

        // gravity
        player._physics_component->applyGravityForce();

        // air movement
        if (_h_movement) {
            player._physics_component->applyHorizontalMovementForce(player.isFacingLeft());
        }

        // standing
        if (player._standing_ray->collided()) {
            player.setState(std::make_shared<IdleState>());
        }

        IPlayerState::physicsUpdate(player);
    }

    void InAirState::handleInput(Player &player, const InputEvent &input) {
        if (input.type == InputEvent::Type::LEFT || input.type == InputEvent::Type::RIGHT) {
            _h_movement = input.state_enter;
        }

        IPlayerState::handleInput(player, input);
    }

    InAirState::InAirState() : _h_movement(false) {

    }
} // game