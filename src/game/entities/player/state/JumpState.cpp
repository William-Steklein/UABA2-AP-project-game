#include "JumpState.h"
#include "FallState.h"

namespace game {
    void JumpState::physicsUpdate(Player &player) {
        if (player._physics_component->getVelocity().y <= 0) {
            player.setState(std::make_shared<FallState>());
        }

        InAirState::physicsUpdate(player);
    }

    void JumpState::enter(Player &player) {
        player._animated_sprite->start("jump", false, player.isFacingLeft());
        player._physics_component->jump();
        player._standing_ray->reset();
    }
} // game