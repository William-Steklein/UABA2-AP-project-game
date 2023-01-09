#ifndef GAME_ENGINE_COLOR_H
#define GAME_ENGINE_COLOR_H


#include <cstdint>

namespace engine {

    struct Color {
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
                : r(red), g(green), b(blue), a(alpha) {}

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

} // engine

#endif //GAME_ENGINE_COLOR_H
