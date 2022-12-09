#include "FallState.h"
#include "IdleState.h"

namespace game {
    void FallState::enter(Player &player) {
        player._animated_sprite->start("fall", true, player.isFacingLeft());
    }
} // game