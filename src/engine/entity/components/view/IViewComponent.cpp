#include "IViewComponent.h"

namespace engine {
    IViewComponent::IViewComponent() : _size(1.f, 1.f), _texture_index(0), _mirror_h(false), _mirror_v(false) {

    }

    void IViewComponent::setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) {
        _texture_index = texture_index;
        _mirror_h = mirror_h;
        _mirror_v = mirror_v;
    }
} // engine