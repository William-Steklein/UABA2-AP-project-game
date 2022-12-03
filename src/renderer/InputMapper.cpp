#include "InputMapper.h"

namespace renderer {
    InputMapper::InputMapper(const std::shared_ptr<sf::RenderWindow> &window)
            : _window(std::move(window)) {

    }

    std::vector<engine::Input> InputMapper::getCurrentInput() {
        std::vector<engine::Input> current_input;

//        std::vector<engine::Input::Button>

//        sf::Keyboard::isKeyPressed();
//        sf::Mouse::isButtonPressed();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _pressed_buttons.insert(engine::Input::Button::A);
            _current_input.push_back(engine::Input());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            _pressed_buttons.insert(engine::Input::Button::B);
            _current_input.push_back(engine::Input());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            _pressed_buttons.insert(engine::Input::Button::C);
            _current_input.push_back(engine::Input());
        }


        return current_input;
    }
} // renderer