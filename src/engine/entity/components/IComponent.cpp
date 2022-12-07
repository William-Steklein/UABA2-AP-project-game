#include "IComponent.h"

namespace engine {
    std::shared_ptr<Transform> IComponent::getTransform() {
        if (_transform.expired()) {
            throw std::runtime_error("Component has no transform");
        }
        return _transform.lock();
    }

    void IComponent::setTransform(std::weak_ptr<Transform> transform) {
        _transform = std::move(transform);
    }

    const Transform &IComponent::getRelativeTransform() const {
        return _relative_transform;
    }

    void IComponent::setRelativeTransform(const Transform &relativeTransform) {
        _relative_transform = relativeTransform;
    }

    Vector2f IComponent::getPosition() {
        return getTransform()->position + _relative_transform.position;
    }

    Vector2f IComponent::getScale() {
        return {getTransform()->scale.x * _relative_transform.scale.x,
                getTransform()->scale.y * _relative_transform.scale.y};
    }

    float IComponent::getRotation() {
        return getTransform()->rotation + _relative_transform.rotation;
    }
} // engine