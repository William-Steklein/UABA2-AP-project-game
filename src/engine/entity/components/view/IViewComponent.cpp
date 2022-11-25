#include "IViewComponent.h"

namespace engine {
    IViewComponent::IViewComponent(const Vector2f &size, std::weak_ptr<Camera> camera)
            : _size(size), _camera(std::move(camera)) {

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
} // engine