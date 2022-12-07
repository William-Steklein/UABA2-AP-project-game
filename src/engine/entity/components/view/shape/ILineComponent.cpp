#include "ILineComponent.h"

namespace engine {
    ILineComponent::ILineComponent(std::weak_ptr<Camera> camera, bool project_ui_space)
            : IShapeComponent({0, 0}, std::move(camera), project_ui_space),
            _line_thickness(0.01f), _shape_rotation(0) {

    }

    const Vector2f &ILineComponent::getOrigin() const {
        return _origin;
    }

    void ILineComponent::setOrigin(const Vector2f &origin) {
        _origin = origin;
        updateLineSize();
        updateShapeRotation();
    }

    const Vector2f &ILineComponent::getEnd() const {
        return _end;
    }

    void ILineComponent::setEnd(const Vector2f &end) {
        _end = end;
        updateLineSize();
        updateShapeRotation();
    }

    void ILineComponent::setLine(const Vector2f &origin, const Vector2f &end) {
        _origin = origin;
        _end = end;
        updateLineSize();
        updateShapeRotation();
    }

    float ILineComponent::getLineThickness() const {
        return _line_thickness;
    }

    void ILineComponent::setLineThickness(float line_thickness) {
        _line_thickness = line_thickness;
        _size.y = line_thickness;
    }

    Vector2f ILineComponent::getLineVector() const {
        return _end - _origin;
    }

    void ILineComponent::updateLineSize() {
        _size.x = (_end - _origin).length();
        _size.y = _line_thickness;
    }

    void ILineComponent::updateShapeRotation() {
        if (_size.x == 0) return;

        // dot product line vector with x-axis elementary vector
        _shape_rotation = std::acos(getLineVector().dotProduct({1, 0}) / _size.x);
    }

    Vector2f ILineComponent::getPosition() {
        return IComponent::getPosition() + _origin + (getLineVector() / 2);
    }

    float ILineComponent::getRotation() {
        return IComponent::getRotation() + _shape_rotation;
    }
} // engine