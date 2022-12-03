#ifndef GAME_ENGINE_INPUTMAPPER_H
#define GAME_ENGINE_INPUTMAPPER_H


#include <memory>
#include <set>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <engine/Input.h>

namespace renderer {

    class InputMapper {
    public:
        InputMapper(const std::shared_ptr<sf::RenderWindow> &window);

        std::vector<engine::Input> getCurrentInput();

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::set<engine::Input::Button> _pressed_buttons;
        std::vector<engine::Input> _current_input;
    };

} // renderer

#endif //GAME_ENGINE_INPUTMAPPER_H
