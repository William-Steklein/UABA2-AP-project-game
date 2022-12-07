#include "Transform.h"

namespace engine {
    Transform::Transform()
            : position(0, 0), scale(1, 1), rotation(0) {}

    Transform::Transform(const Vector2f &new_position, const Vector2f &new_scale, float new_rotation)
            : position(new_position), scale(new_scale), rotation(new_rotation) {}

    void Transform::move(const Vector2f &vector) {
        position += vector;
    }
} // engine