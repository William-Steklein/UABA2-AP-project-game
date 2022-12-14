#include "InputMapper.h"

namespace renderer {
    InputMapper::InputMapper(const std::shared_ptr<sf::RenderWindow> &window)
            : _window(std::move(window)) {

    }

    void InputMapper::checkMouseButtonInput() {
        std::map<sf::Mouse::Button, engine::Input::Button> keyboard_button_map = {
                {sf::Mouse::Left,   engine::Input::Button::MOUSELEFT},
                {sf::Mouse::Middle, engine::Input::Button::MOUSEMIDDLE},
                {sf::Mouse::Right,  engine::Input::Button::MOUSERIGHT},
        };

        for (const auto &key_pair: keyboard_button_map) {
            engine::Input input{};

            auto button_it = _pressed_buttons.find(key_pair.second);

            if (sf::Mouse::isButtonPressed(key_pair.first)) {
                if (button_it == _pressed_buttons.end()) {
                    _pressed_buttons.insert(key_pair.second);
                    input.type = engine::Input::InputType::BUTTONPRESSED;
                } else {
                    input.type = engine::Input::InputType::BUTTONPRESSING;
                }

            } else {
                if (button_it == _pressed_buttons.end()) {
                    continue;
                }

                _pressed_buttons.erase(button_it);
                input.type = engine::Input::InputType::BUTTONRELEASED;
            }

            input.button = key_pair.second;
            _current_input.push_back(input);
        }
    }

    void InputMapper::checkKeyboardButtonInput() {
        std::map<sf::Keyboard::Key, engine::Input::Button> keyboard_button_map = {
                {sf::Keyboard::A,        engine::Input::Button::A},
                {sf::Keyboard::B,        engine::Input::Button::B},
                {sf::Keyboard::C,        engine::Input::Button::C},
                {sf::Keyboard::D,        engine::Input::Button::D},
                {sf::Keyboard::E,        engine::Input::Button::E},
                {sf::Keyboard::F,        engine::Input::Button::F},
                {sf::Keyboard::G,        engine::Input::Button::G},
                {sf::Keyboard::H,        engine::Input::Button::H},
                {sf::Keyboard::I,        engine::Input::Button::I},
                {sf::Keyboard::J,        engine::Input::Button::J},
                {sf::Keyboard::K,        engine::Input::Button::K},
                {sf::Keyboard::L,        engine::Input::Button::L},
                {sf::Keyboard::M,        engine::Input::Button::M},
                {sf::Keyboard::N,        engine::Input::Button::N},
                {sf::Keyboard::O,        engine::Input::Button::O},
                {sf::Keyboard::P,        engine::Input::Button::P},
                {sf::Keyboard::Q,        engine::Input::Button::Q},
                {sf::Keyboard::R,        engine::Input::Button::R},
                {sf::Keyboard::S,        engine::Input::Button::S},
                {sf::Keyboard::T,        engine::Input::Button::T},
                {sf::Keyboard::U,        engine::Input::Button::U},
                {sf::Keyboard::V,        engine::Input::Button::V},
                {sf::Keyboard::W,        engine::Input::Button::W},
                {sf::Keyboard::X,        engine::Input::Button::X},
                {sf::Keyboard::Y,        engine::Input::Button::Y},
                {sf::Keyboard::Z,        engine::Input::Button::Z},
                {sf::Keyboard::LControl, engine::Input::Button::CONTROL},
                {sf::Keyboard::RControl, engine::Input::Button::CONTROL},
                {sf::Keyboard::LShift,   engine::Input::Button::SHIFT},
                {sf::Keyboard::RShift,   engine::Input::Button::SHIFT},
                {sf::Keyboard::Tab,      engine::Input::Button::TAB},
                {sf::Keyboard::Escape,   engine::Input::Button::ESCAPE},
                {sf::Keyboard::Space,    engine::Input::Button::SPACEBAR},
                {sf::Keyboard::Enter,    engine::Input::Button::ENTER},
        };

        for (const auto &key_pair: keyboard_button_map) {
            engine::Input input{};

            auto button_it = _pressed_buttons.find(key_pair.second);

            if (sf::Keyboard::isKeyPressed(key_pair.first)) {
                if (button_it == _pressed_buttons.end()) {
                    _pressed_buttons.insert(key_pair.second);
                    input.type = engine::Input::InputType::BUTTONPRESSED;
                } else {
                    input.type = engine::Input::InputType::BUTTONPRESSING;
                }

            } else {
                if (button_it == _pressed_buttons.end()) {
                    continue;
                }

                _pressed_buttons.erase(button_it);
                input.type = engine::Input::InputType::BUTTONRELEASED;
            }

            input.button = key_pair.second;
            _current_input.push_back(input);
        }
    }

    void InputMapper::checkMouseMovement() {
        sf::Vector2<int> mouse_position = sf::Mouse::getPosition(*_window);
        if (_mouse_position != mouse_position) {
            _mouse_position = mouse_position;

            engine::Input input{};
            input.type = engine::Input::InputType::MOUSEMOVED;
            input.range_2d = {static_cast<float>(_mouse_position.x),
                              static_cast<float>(_mouse_position.y)};

            _current_input.push_back(input);
        }
    }

    std::vector<engine::Input> InputMapper::getCurrentInput() {
        _current_input.clear();

        checkMouseButtonInput();
        checkKeyboardButtonInput();
        checkMouseMovement();

        return _current_input;
    }
} // renderer