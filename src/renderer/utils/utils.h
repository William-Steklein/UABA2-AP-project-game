#ifndef GAME_ENGINE_UTILS_H
#define GAME_ENGINE_UTILS_H


#include <SFML/Graphics/Color.hpp>

#include "engine/utils/Color.h"

namespace renderer {

    sf::Color colorEngineToSFML(const engine::Color &color);

} // renderer

#endif //GAME_ENGINE_UTILS_H
