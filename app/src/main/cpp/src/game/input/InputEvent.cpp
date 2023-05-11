#include "InputEvent.h"

namespace game {
    game::InputEvent::State mapEngineToGameInputType(engine::Input::InputType input) {
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

    game::InputEvent::Range2D EngineToGameInputRange2D(engine::Input::Range2D input) {
        return {input.x, input.y};
    }

    engine::Vector2f Range2DToVector2f(game::InputEvent::Range2D input) {
        return {input.x, input.y};
    }

    game::InputEvent::Range2D Vector2fToRange2D(const engine::Vector2f &input) {
        return {input.x, input.y};
    }
} // game