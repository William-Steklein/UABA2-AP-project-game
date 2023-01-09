#ifndef GAME_ENGINE_INPUTCHECKER_H
#define GAME_ENGINE_INPUTCHECKER_H


#include <memory>
#include <set>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/input/Input.h"

namespace renderer {

    class InputChecker {
    public:
        InputChecker(const std::shared_ptr<sf::RenderWindow> &window);

        void checkMouseButtonInput();

        void checkKeyboardButtonInput();

        void checkMouseMovement();

        std::vector<engine::Input> getCurrentInput();

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::set<engine::Input::Button> _pressed_buttons;
        std::vector<engine::Input> _current_input;

        sf::Vector2<int> _mouse_position;
    };

} // renderer

#endif //GAME_ENGINE_INPUTCHECKER_H
