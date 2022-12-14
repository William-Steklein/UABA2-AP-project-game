#include "WallSlideState.h"
#include "FallState.h"
#include "IdleState.h"
#include "JumpState.h"

namespace game {
    void WallSlideState::enter(Player &player) {
        // reverse direction
        player.updateDirection(player.isFacingLeft() ? Player::Direction::RIGHT : Player::Direction::LEFT);

        player._animated_sprite->start("wall_slide", true, player.isFacingLeft());

        player._physics_component->setVelocity({0, 0});
        player._physics_component->setWallVelocityClamp(true);
    }

    void WallSlideState::exit(Player &player) {
        player._physics_component->setWallVelocityClamp(false);
    }

    void WallSlideState::physicsUpdate(game::Player &player) {
        player._physics_component->applyGravityForce(0.25f);

        if ((!player.isFacingLeft() && !player._left_wall_slide_ray->collided()) ||
            (player.isFacingLeft() && !player._right_wall_slide_ray->collided())) {
            player.setState(std::make_shared<FallState>());
        }

        if (player._standing_ray->collided()) {
            player.setState(std::make_shared<IdleState>());
        }

        IPlayerState::physicsUpdate(player);
    }

    void WallSlideState::handleInput(Player &player, const InputEvent &input) {
        if ((input.type == InputEvent::Type::LEFT && player.isFacingLeft()) ||
            (input.type == InputEvent::Type::RIGHT && !player.isFacingLeft())) {
            player.setState(std::make_shared<FallState>());
        }

        if (input.type == InputEvent::Type::JUMP) {
            if (input.state == InputEvent::State::ENTERED) {
                player._physics_component->setVelocity({0, 0});
                player.setState(std::make_shared<JumpState>(true));
            }
        }

//        IPlayerState::handleInput(player, input);
    }
}