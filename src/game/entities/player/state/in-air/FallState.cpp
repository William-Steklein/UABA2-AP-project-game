#include "FallState.h"
#include "game/entities/player/state/on-ground/IdleState.h"

namespace game {
    void FallState::enter() {
        _player._animated_sprite->start("fall", true, _player.isFacingLeft());
    }
} // game