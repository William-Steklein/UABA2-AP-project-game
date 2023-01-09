#include "FallState.h"

namespace game {
    void FallState::enter() {
        _state_machine._animated_sprite->start("fall", true, _state_machine.isFacingLeft(), false);
    }
} // game