#include "InAirState.h"
#include "IdleState.h"
#include "WallSlideState.h"

namespace game {
    void InAirState::physicsUpdate(Player &player) {
        // gravity
        player._physics_component->applyGravityForce();

        // air movement
        if (_h_movement) {
            player._physics_component->applyHorizontalMovementForce(player.isFacingLeft());
        }

        // wall slide
        if (player.isFacingLeft() && player._left_wall_slide_ray->collided() ||
            !player.isFacingLeft() && player._right_wall_slide_ray->collided()) {
            player.setState(std::make_shared<WallSlideState>());
        }

        // standing
        if (player._standing_ray->collided()) {
            player.setState(std::make_shared<IdleState>());
        }

        IPlayerState::physicsUpdate(player);
    }

    void InAirState::handleInput(Player &player, const InputEvent &input) {
        if (input.type == InputEvent::Type::LEFT || input.type == InputEvent::Type::RIGHT) {
            _h_movement = (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE);
        }

        IPlayerState::handleInput(player, input);
    }

    InAirState::InAirState() : _h_movement(false) {

    }
} // game