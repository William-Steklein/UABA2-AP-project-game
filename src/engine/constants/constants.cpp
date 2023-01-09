#include "engine/constants/constants.h"

namespace engine {
    namespace constants {

        const float framerate_limit = 60.f;
        const bool cap_framerate = true;

        const float sample_duration = 0.5f;

        const float physics_delta_time = 1 / 60.f;

        const float animation_frame_time_minimum = 0.001f;

        const float velocity_epsilon = 1.e-4f;

    } // constants
} // engine