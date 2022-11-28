#ifndef GAME_ENGINE_INPUT_MAPPING_H
#define GAME_ENGINE_INPUT_MAPPING_H


#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <engine/Input.h>

namespace renderer {

    engine::Input mapInput(const sf::Event &event, const std::shared_ptr<sf::RenderWindow> &window);

    engine::Input::Button _mapKeyboardInput(const sf::Event &event);

    engine::Input::Button _mapMouseButtonInput(const sf::Event &event);

    engine::Input::Range2D _mapMouseMovement(const sf::Event &event, const std::shared_ptr<sf::RenderWindow> &window);

} // renderer

#endif //GAME_ENGINE_INPUT_MAPPING_H
