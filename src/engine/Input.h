#ifndef GAME_ENGINE_INPUT_H
#define GAME_ENGINE_INPUT_H


#include "engine/math/Vector2f.h"

namespace engine {

    struct Input {
        enum InputType {
            UNDEFINED_TYPE,
            KEYPRESSED,
            KEYRELEASED,
            MOUSEPRESSED,
            MOUSERELEASED,
            MOUSEMOVED
        };

        enum Button {
            UNDEFINED_BUTTON,
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

            ESCAPE,
            SPACEBAR,

            MOUSELEFT,
            MOUSERIGHT,
            MOUSEMIDDLE
        };

        struct Range2D {
            float x;
            float y;
        };

        InputType type;

        union {
            Button button;
            Range2D range_2d;
            float range;
        };
    };

} // engine

#endif //GAME_ENGINE_INPUT_H
