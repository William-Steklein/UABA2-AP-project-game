#include "IViewComponentCreator.h"

namespace engine {
    void IViewComponentCreator::setCamera(std::weak_ptr<Camera> camera) {
        _camera = std::move(camera);
    }
} // engine
