#ifndef GAME_ENGINE_CONSTANTS_H
#define GAME_ENGINE_CONSTANTS_H


#include <engine/math/Vector2f.h>

namespace game {

    namespace constants {

        namespace player {

            extern const engine::Vector2f view_size;

            extern const float jump_dt;
            extern const float jump_height;

            extern const float mass;
            extern const float horizontal_movement_force;

        } // player

    } // constants

} // game

#endif //GAME_ENGINE_CONSTANTS_H
