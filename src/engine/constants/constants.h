#ifndef GAME_ENGINE_CONSTANTS_ENGINE_H
#define GAME_ENGINE_CONSTANTS_ENGINE_H

namespace engine {

    namespace constants {

        // framerate limit control
        extern const float framerate_limit;
        extern const bool cap_framerate;

        // average framerate counter
        extern const float sample_duration;

        extern const float physics_delta_time;

        extern const float animation_frame_time_minimum;

        // velocities under this value are set to zero
        extern const float velocity_epsilon;

    } // constants

} // engine

#endif //GAME_ENGINE_CONSTANTS_ENGINE_H
