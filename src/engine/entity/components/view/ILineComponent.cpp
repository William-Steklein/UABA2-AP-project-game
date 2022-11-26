#include "ILineComponent.h"

namespace engine {
    ILineComponent::ILineComponent(const Vector2f &size, std::weak_ptr<Camera> camera,
                                   const Vector2f &origin, const Vector2f &end)
            : IShapeComponent(size, std::move(camera)),
            _origin(origin), _end(end), _line_thickness(0.01f),
            _shape_rotation(getShapeRotation()) {

    }

    const Vector2f &ILineComponent::getOrigin() const {
        return _origin;
    }

    void ILineComponent::setOrigin(const Vector2f &origin) {
        _origin = origin;
    }

    const Vector2f &ILineComponent::getEnd() const {
        return _end;
    }

    void ILineComponent::setEnd(const Vector2f &end) {
        _end = end;
    }

    float ILineComponent::getLineThickness() const {
        return _line_thickness;
    }

    void ILineComponent::setLineThickness(float line_thickness) {
        _line_thickness = line_thickness;
    }

    float ILineComponent::getShapeRotation() {
        // dot product line vector with x-axis elementary vector
        Vector2f line_vec = _end - _origin;
        float line_vec_length = line_vec.length();

        if (line_vec_length == 0) return 0;
        return std::acos(line_vec.dotProduct({1, 0}) / line_vec_length);
    }
} // engine