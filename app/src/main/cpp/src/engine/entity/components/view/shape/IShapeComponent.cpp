#include "IShapeComponent.h"

namespace engine {
    const Color &IShapeComponent::getFillcolor() const {
        return _fillcolor;
    }

    void IShapeComponent::setFillcolor(const Color &fillcolor) {
        _fillcolor = fillcolor;
        updateShape();
    }

    const Color &IShapeComponent::getOutlineColor() const {
        return _outline_color;
    }

    void IShapeComponent::setOutlineColor(const Color &outline_color) {
        _outline_color = outline_color;
        updateShape();
    }

    float IShapeComponent::getOutlineThickness() const {
        return _outline_thickness;
    }

    void IShapeComponent::setOutlineThickness(float outline_thickness) {
        _outline_thickness = outline_thickness;
        updateShape();
    }

    IShapeComponent::IShapeComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space)
            : IViewComponent(size, std::move(camera), project_ui_space),
              _fillcolor(0, 0, 0), _outline_color(0, 0, 0), _outline_thickness(0) {

    }
} // engine