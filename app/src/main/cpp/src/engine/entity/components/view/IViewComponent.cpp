#include "IViewComponent.h"

namespace engine {
    IViewComponent::IViewComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space)
            : _size(size), _camera(std::move(camera)), _project_ui_space(project_ui_space), _visible(true) {

    }

    const Vector2f &IViewComponent::getSize() const {
        return _size;
    }

    void IViewComponent::setSize(const Vector2f &size) {
        _size = size;
    }

    const std::weak_ptr<Camera> &IViewComponent::getCamera() const {
        return _camera;
    }

    void IViewComponent::setCamera(const std::weak_ptr<Camera> &camera) {
        _camera = camera;
    }

    bool IViewComponent::isVisible() const {
        return _visible;
    }

    void IViewComponent::setVisible(bool visible) {
        _visible = visible;
        update(0, 0);
    }

    Vector2f IViewComponent::getScale() {
        if (_visible) {
            return IComponent::getScale();
        } else {
            return {0, 0};
        }
    }
} // engine