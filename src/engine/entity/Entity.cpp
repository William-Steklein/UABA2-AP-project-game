#include "engine/entity/Entity.h"

namespace engine {
    Entity::Entity(Transform transform, const std::vector<std::shared_ptr<IComponent>>& components)
            : _transform(std::move(transform)) {
        addComponents(components);
    }

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
        setPosition(transform.position);
        setScale(transform.scale);
        setRotation(transform.rotation);
    }

    const Vector2f &Entity::getPosition() const {
        return _transform.position;
    }

    void Entity::setPosition(const Vector2f &position) {
        _transform.position = position;
    }

    void Entity::move(const engine::Vector2f &vector) {
        setPosition(getPosition() + vector);
    }

    const Vector2f &Entity::getScale() const {
        return _transform.scale;
    }

    void Entity::setScale(const Vector2f &scale) {
        _transform.scale = scale;
    }

    void Entity::scale(const engine::Vector2f &scale) {
        setScale({getScale().x * scale.x, getScale().y * scale.y});
    }

    const float &Entity::getRotation() const {
        return _transform.rotation;
    }

    void Entity::setRotation(const float &rotation) {
        _transform.rotation = rotation;
    }

    void Entity::rotate(float rotation) {
        setRotation(getRotation() + rotation);
    }

    void Entity::addComponent(std::shared_ptr<IComponent> component) {
        checkComponent(component);
        _components.push_back(std::move(component));
    }

    void Entity::addComponents(const std::vector<std::shared_ptr<IComponent>>& components) {
        for (auto component : components) {
            checkComponent(component);
            _components.push_back(std::move(component));
        }
    }

    void Entity::removeComponent(const std::shared_ptr<IComponent>& component) {
        auto it = std::find(_components.begin(), _components.end(), component);
        if (it != _components.end()) {
            _components.erase(it);
        }
    }

    void Entity::checkComponent(const std::shared_ptr<IComponent> &component) {
        if (!component.get()) {
            throw std::runtime_error("Entity has an empty component");
        }
    }
} // engine