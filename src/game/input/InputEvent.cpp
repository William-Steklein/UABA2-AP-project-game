#include "InputEvent.h"

namespace game {
    game::InputEvent::State mapEngineToGameInput(engine::Input::InputType input) {
        switch (input) {
            case engine::Input::InputType::BUTTONPRESSED:
                return game::InputEvent::State::ENTERED;

            case engine::Input::InputType::BUTTONPRESSING:
                return game::InputEvent::State::ACTIVE;

            case engine::Input::InputType::BUTTONRELEASED:
                return game::InputEvent::State::EXITED;

            default:
                throw std::runtime_error("Unable to map engine to game input");
        }
    }
} // game