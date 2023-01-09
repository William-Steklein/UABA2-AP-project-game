#ifndef GAME_ENGINE_CONSTANTS_ENGINE_H
#define GAME_ENGINE_CONSTANTS_ENGINE_H

#include "engine/math/Vector2f.h"

namespace engine {

    namespace constants {

        // framerate limit control
        extern const float framerate_limit;
        extern const bool framerate_cap;
        extern const bool show_framerate;

        // average framerate counter
        extern const float sample_duration;

        extern const float physics_framerate_limit;

        extern const float animation_frame_time_minimum;

        // velocities under this value are set to zero
        extern const float velocity_epsilon;

        namespace camera {

            extern const Vector2f x_boundary;
            extern const Vector2f y_boundary;

            extern const Vector2f aspect_ratio;

        }


    } // constants

} // engine

#endif //GAME_ENGINE_CONSTANTS_ENGINE_H
