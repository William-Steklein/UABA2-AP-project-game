#include "WallSlideState.h"
#include "FallState.h"
#include "IdleState.h"

namespace game {
    void WallSlideState::enter(Player &player) {
        // reverse direction
        player.updateDirection(player.isFacingLeft() ? Player::Direction::RIGHT : Player::Direction::LEFT);

        player._animated_sprite->start("wall_slide", true, player.isFacingLeft());

        if (player._physics_component->getVelocity().y > 0) {
            player._physics_component->setVelocity({0, 0});
        }
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


        if (input.state_enter) {
            switch (input.type) {
                case InputEvent::Type::LEFT:
                    player.updateDirection(Player::Direction::LEFT);
                    break;

                case InputEvent::Type::RIGHT:
                    player.updateDirection(Player::Direction::RIGHT);
                    break;

                default:
                    break;
            }
        }

//        IPlayerState::handleInput(player, input);
    }
}