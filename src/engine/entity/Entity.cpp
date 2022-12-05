#include "engine/entity/Entity.h"

namespace engine {
    Entity::Entity(Transform transform, const std::vector<std::shared_ptr<IComponent>> &components) {
        _transform = std::make_shared<Transform>();
        *_transform = std::move(transform);
        addComponents(components);
    }

    void Entity::physicsUpdate(double t, float dt) {
        for (const auto &component: _components_physics) {
            if (component.get()) {
                component->update(t, dt);
            }
        }
    }

    void Entity::graphicsUpdate(double t, float dt) {
        for (const auto &component: _components_graphics) {
            if (component.get()) {
                component->update(t, dt);
            }
        }
    }

    const std::shared_ptr<Transform> &Entity::getTransform() const {
        return _transform;
    }

    const Vector2f &Entity::getPosition() const {
        return _transform->position;
    }

    void Entity::setPosition(const Vector2f &position) {
        _transform->position = position;
    }

    void Entity::move(const engine::Vector2f &vector) {
        _transform->move(vector);
    }

    const Vector2f &Entity::getScale() const {
        return _transform->scale;
    }

    void Entity::setScale(const Vector2f &scale) {
        _transform->scale = scale;
    }

    void Entity::scale(const engine::Vector2f &scale) {
        setScale({getScale().x * scale.x, getScale().y * scale.y});
    }

    const float &Entity::getRotation() const {
        return _transform->rotation;
    }

    void Entity::setRotation(const float &rotation) {
        _transform->rotation = rotation;
    }

    void Entity::rotate(float rotation) {
        setRotation(getRotation() + rotation);
    }

    void Entity::addComponent(std::shared_ptr<IComponent> component, bool physics) {
        checkComponent(component);
        component->setTransform(_transform);
        component->update(0, 0);
        if (physics) {
            _components_physics.push_back(std::move(component));
        } else {
            _components_graphics.push_back(std::move(component));
        }
    }

    void Entity::addComponents(const std::vector<std::shared_ptr<IComponent>> &components, bool physics) {
        for (const auto &component: components) {
            addComponent(component, physics);
        }
    }

    void Entity::checkComponent(const std::shared_ptr<IComponent> &component) {
        if (!component.get()) {
            throw std::runtime_error("Entity has an empty component");
        }
    }
} // engine