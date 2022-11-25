#include "engine/entity/Entity.h"

namespace engine {
    Entity::Entity(const Transform &transform)
            : _transform(transform) {

    }

    Entity::~Entity() = default;

    void Entity::update(double t, float dt) {
        for (const auto &component: _components) {
            if (component.get()) {
                component->update(t, dt, *this);
            }
        }
    }

    const Transform &Entity::getTransform() const {
        return _transform;
    }

    void Entity::setTransform(const Transform &transform) {
        _transform = transform;
    }

    const Vector2f &Entity::getPosition() const {
        return _transform.position;
    }

    void Entity::setPosition(const Vector2f &position) {
        _transform.position = position;
    }

    const Vector2f &Entity::getScale() const {
        return _transform.scale;
    }

    void Entity::setScale(const Vector2f &scale) {
        _transform.scale = scale;
    }

    const float &Entity::getRotation() const {
        return _transform.rotation;
    }

    void Entity::setRotation(const float &rotation) {
        _transform.rotation = rotation;
    }

    void Entity::checkComponent(const std::shared_ptr<IComponent> &component) {
        if (!component.get()) {
            throw std::runtime_error("Entity has an empty component");
        }
    }
} // engine