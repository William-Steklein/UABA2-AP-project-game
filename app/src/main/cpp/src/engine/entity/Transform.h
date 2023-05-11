#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H


#include "engine/math/Vector2f.h"

namespace engine {

    struct Transform {
        Vector2f position;
        Vector2f scale;
        float rotation;

        Transform();

        Transform(const Vector2f &new_position, const Vector2f &new_scale, float new_rotation);

        void move(const Vector2f &vector);
    };

} // engine

#endif //GAME_ENGINE_TRANSFORM_H
