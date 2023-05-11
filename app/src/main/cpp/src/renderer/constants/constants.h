#ifndef GAME_ENGINE_CONSTANTS_RENDERER_H
#define GAME_ENGINE_CONSTANTS_RENDERER_H


#include <string>
#include "engine/utils/Color.h"

namespace renderer {

    namespace constants {

        extern const unsigned int screen_width;
        extern const unsigned int screen_height;
        extern const std::string window_title;

        extern const engine::Color window_clear_color;

    }; // constants

} // renderer

#endif //GAME_ENGINE_CONSTANTS_RENDERER_H
