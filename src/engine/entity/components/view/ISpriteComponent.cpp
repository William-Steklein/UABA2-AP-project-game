#include "ISpriteComponent.h"

namespace engine {
    ISpriteComponent::ISpriteComponent(const Vector2f &size, std::weak_ptr<Camera> camera)
            : IViewComponent(size, std::move(camera)),
              _texture_index(0), _mirror_h(false), _mirror_v(false) {

    }

    void ISpriteComponent::setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) {
        _texture_index = texture_index;
        _mirror_h = mirror_h;
        _mirror_v = mirror_v;
    }
} // engine