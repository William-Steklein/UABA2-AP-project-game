#include "utils.h"

namespace renderer {
    sf::Color colorEngineToSFML(const engine::Color &color) {
        return {color.r, color.g, color.b, color.a};
    }
} // renderer