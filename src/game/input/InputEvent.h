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

            DEBUGVIEW,
        };

        enum State {
            ENTERED,
            ACTIVE,
            EXITED
        };

        Type type;
        State state;

        float range;
    };

    game::InputEvent::State mapEngineToGameInput(engine::Input::InputType input);

} // game

#endif //GAME_ENGINE_INPUTEVENT_H
