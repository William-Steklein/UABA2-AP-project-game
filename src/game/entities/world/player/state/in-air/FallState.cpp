#include "FallState.h"
#include "game/entities/world/player/state/on-ground/IdleState.h"

namespace game {
    void FallState::enter() {
        _state_machine._animated_sprite->start("fall", true, _state_machine.isFacingLeft(), false);
    }
} // game