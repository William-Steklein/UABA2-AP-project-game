#include "input_mapping.h"

namespace renderer {
    engine::Input mapInput(const sf::Event &event, const std::shared_ptr<sf::RenderWindow> &window) {
        engine::Input input{engine::Input::InputType::UNDEFINEDTYPE};

        switch (event.type) {
            case sf::Event::KeyPressed:
                input.type = engine::Input::InputType::KEYPRESSED;
                input.button = _mapKeyboardInput(event);
                break;

            case sf::Event::KeyReleased:
                input.type = engine::Input::InputType::KEYRELEASED;
                input.button = _mapKeyboardInput(event);
                break;

            case sf::Event::MouseButtonPressed:
                input.type = engine::Input::InputType::MOUSEPRESSED;
                input.button = _mapMouseButtonInput(event);
                break;

            case sf::Event::MouseButtonReleased:
                input.type = engine::Input::InputType::MOUSERELEASED;
                input.button = _mapMouseButtonInput(event);
                break;

            case sf::Event::MouseMoved:
                input.type = engine::Input::InputType::MOUSEMOVED;
                input.range_2d = _mapMouseMovement(event, window);
                break;

            default:
                break;
        }

        if (input.button == engine::Input::Button::UNDEFINEDBUTTON) {
            input.type = engine::Input::InputType::UNDEFINEDTYPE;
        }

        return input;
    }

    engine::Input::Button _mapKeyboardInput(const sf::Event &event) {
        switch (event.key.code) {
            case sf::Keyboard::A:
                return engine::Input::Button::A;

            case sf::Keyboard::B:
                return engine::Input::Button::B;

            case sf::Keyboard::C:
                return engine::Input::Button::C;

            case sf::Keyboard::D:
                return engine::Input::Button::D;

            case sf::Keyboard::E:
                return engine::Input::Button::E;

            case sf::Keyboard::F:
                return engine::Input::Button::F;

            case sf::Keyboard::G:
                return engine::Input::Button::G;

            case sf::Keyboard::H:
                return engine::Input::Button::H;

            case sf::Keyboard::I:
                return engine::Input::Button::I;

            case sf::Keyboard::J:
                return engine::Input::Button::J;

            case sf::Keyboard::K:
                return engine::Input::Button::K;

            case sf::Keyboard::L:
                return engine::Input::Button::L;

            case sf::Keyboard::M:
                return engine::Input::Button::M;

            case sf::Keyboard::N:
                return engine::Input::Button::N;

            case sf::Keyboard::O:
                return engine::Input::Button::O;

            case sf::Keyboard::P:
                return engine::Input::Button::P;

            case sf::Keyboard::Q:
                return engine::Input::Button::Q;

            case sf::Keyboard::R:
                return engine::Input::Button::R;

            case sf::Keyboard::S:
                return engine::Input::Button::S;

            case sf::Keyboard::T:
                return engine::Input::Button::T;

            case sf::Keyboard::U:
                return engine::Input::Button::U;

            case sf::Keyboard::V:
                return engine::Input::Button::V;

            case sf::Keyboard::W:
                return engine::Input::Button::W;

            case sf::Keyboard::X:
                return engine::Input::Button::X;

            case sf::Keyboard::Y:
                return engine::Input::Button::Y;

            case sf::Keyboard::Z:
                return engine::Input::Button::Z;

            case sf::Keyboard::Left:
                return engine::Input::Button::LEFT;

            case sf::Keyboard::Right:
                return engine::Input::Button::RIGHT;

            case sf::Keyboard::Down:
                return engine::Input::Button::DOWN;

            case sf::Keyboard::Up:
                return engine::Input::Button::UP;

            case sf::Keyboard::LControl:
            case sf::Keyboard::RControl:
                return engine::Input::Button::CONTROL;

            case sf::Keyboard::LShift:
            case sf::Keyboard::RShift:
                return engine::Input::Button::SHIFT;

            case sf::Keyboard::Tab:
                return engine::Input::Button::TAB;

            case sf::Keyboard::Escape:
                return engine::Input::Button::ESCAPE;

            case sf::Keyboard::Space:
                return engine::Input::Button::SPACEBAR;

            default:
                return engine::Input::Button::UNDEFINEDBUTTON;
        }
    }

    engine::Input::Button _mapMouseButtonInput(const sf::Event &event) {
        switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                return engine::Input::Button::MOUSELEFT;

            case sf::Mouse::Middle:
                return engine::Input::Button::MOUSEMIDDLE;

            case sf::Mouse::Right:
                return engine::Input::Button::MOUSERIGHT;

            default:
                return engine::Input::Button::UNDEFINEDBUTTON;
        }
    }

    engine::Input::Range2D _mapMouseMovement(const sf::Event &event, const std::shared_ptr<sf::RenderWindow> &window) {
        return {static_cast<float>(sf::Mouse::getPosition(*window).x) / static_cast<float>(window->getSize().x),
                1.f -
                (static_cast<float>(sf::Mouse::getPosition(*window).y) / static_cast<float>(window->getSize().y))};
    }
} // renderer