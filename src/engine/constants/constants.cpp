#include "engine/constants/constants.h"

namespace engine {
    namespace constants {

        const float framerate_limit = 60.f;
        const bool framerate_cap = true;
        const bool show_framerate = false;

        const float sample_duration = 0.5f;

        const float physics_framerate_limit = 60.f;

        const float animation_frame_time_minimum = 0.001f;

        const float velocity_epsilon = 1.e-4f;

        namespace camera {
            extern const Vector2f x_boundary = {-2.5, 2.5};
            extern const Vector2f y_boundary = {-1.5, 1.5};

            extern const Vector2f aspect_ratio = {5, 3};
        }

    } // constants
} // engine