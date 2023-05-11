#ifndef GAME_ENGINE_INPUTEVENT_H
#define GAME_ENGINE_INPUTEVENT_H


#include "engine/input/Input.h"

namespace game {

    struct InputEvent {
        enum Type {
            UNDEFINED_EVENT,

            LEFT,
            RIGHT,
            DOWN,

            ACCEPT,
            RETURN,

            JUMP,

            MOUSEMOVED,
            MOUSECLICK,

            TOUCH,

            DEBUGVIEW,
        };

        enum State {
            ENTERED,
            ACTIVE,
            EXITED
        };

        struct Range2D {
            float x;
            float y;
        };

        Type type;
        State state;

        union {
            float range;
            Range2D range_2d;
        };

        unsigned int touch_finger;
    };

    game::InputEvent::State mapEngineToGameInputType(engine::Input::InputType input);

    game::InputEvent::Range2D EngineToGameInputRange2D(engine::Input::Range2D input);

    engine::Vector2f Range2DToVector2f(game::InputEvent::Range2D input);

    game::InputEvent::Range2D Vector2fToRange2D(const engine::Vector2f &input);

} // game

#endif //GAME_ENGINE_INPUTEVENT_H
