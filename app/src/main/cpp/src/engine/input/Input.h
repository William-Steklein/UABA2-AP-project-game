#ifndef GAME_ENGINE_INPUT_H
#define GAME_ENGINE_INPUT_H


#include <string>
#include <map>

#include "engine/math/Vector2f.h"

namespace engine {

    struct Input {
        enum InputType {
            UNDEFINEDTYPE,

            BUTTONPRESSED,
            BUTTONPRESSING,
            BUTTONRELEASED,

            MOUSEMOVED
        };

        enum Button {
            UNDEFINEDBUTTON,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            LEFT,
            RIGHT,
            DOWN,
            UP,

            CONTROL,
            SHIFT,
            TAB,
            ESCAPE,
            SPACEBAR,
            ENTER,

            MOUSELEFT,
            MOUSERIGHT,
            MOUSEMIDDLE,

            TOUCH
        };

        struct Range2D {
            float x;
            float y;
        };

        InputType type;

        Button button;

        union {
            float range;
            Range2D range_2d;
        };

        unsigned int touch_finger;
    };

    engine::Input::Button stringToInputButton(const std::string &button);

    std::string inputButtonToString(const engine::Input::Button &button);

} // engine

#endif //GAME_ENGINE_INPUT_H
