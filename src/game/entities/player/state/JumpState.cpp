#include "JumpState.h"
#include "FallState.h"

namespace game {
    JumpState::JumpState(bool wall_jump) : _wall_jump(wall_jump) {
    }

    void JumpState::enter(Player &player) {
        player._animated_sprite->start("jump", false, player.isFacingLeft());

        player._physics_component->jump(_wall_jump, player.isFacingLeft());
        player._standing_ray->reset();
    }

    void JumpState::physicsUpdate(Player &player) {
        if (player._physics_component->getVelocity().y <= 0) {
            player.setState(std::make_shared<FallState>());
        }

        InAirState::physicsUpdate(player);
    }
} // game