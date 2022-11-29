#ifndef GAME_ENGINE_INPUTEVENT_H
#define GAME_ENGINE_INPUTEVENT_H

namespace game {

    struct InputEvent {
        enum Type {
            UNDEFINED_EVENT,

            LEFT,
            RIGHT,
            DOWN,
            UP,

            ACCEPT,
            RETURN,

            JUMP,
            SPECIAL,
        };

        Type type;

        bool state_enter;
        float range;
    };

} // game

#endif //GAME_ENGINE_INPUTEVENT_H
