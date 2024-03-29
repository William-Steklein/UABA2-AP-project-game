#include "ISpriteComponent.h"

namespace engine {
    ISpriteComponent::ISpriteComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space)
            : IViewComponent(size, std::move(camera), project_ui_space),
              _texture_index(0), _mirror_h(false), _mirror_v(false) {

    }

    void ISpriteComponent::setTexture(unsigned int texture_index) {
        _texture_index = texture_index;
        updateSprite();
    }

    void ISpriteComponent::setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) {
        _mirror_h = mirror_h;
        _mirror_v = mirror_v;

        setTexture(texture_index);
    }

    bool ISpriteComponent::isMirrorH() const {
        return _mirror_h;
    }

    void ISpriteComponent::setMirrorH(bool mirror_h) {
        _mirror_h = mirror_h;
        update(0, 0);
    }

    bool ISpriteComponent::isMirrorV() const {
        return _mirror_v;
    }

    void ISpriteComponent::setMirrorV(bool mirror_v) {
        _mirror_v = mirror_v;
        update(0, 0);
    }
} // engine