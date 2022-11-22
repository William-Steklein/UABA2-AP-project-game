#include "engine/entities/Entity.h"

namespace engine {

    Entity::Entity(std::shared_ptr<IEntityView> view, std::shared_ptr<EntityAnimation> animation)
            : _position(0, 0), _scale(1, 1), _rotation(0),
              _view(std::move(view)), _animation(std::move(animation)) {
        if (_animation.get()) {
            _animation->setView(_view);
        }
    }

    Entity::~Entity() = default;

    void Entity::update(double t, float dt) {
        for (const auto &component: std::vector<std::shared_ptr<IEntityComponent>>{_animation, _view}) {
            component->update(t, dt, *this);
        }
    }

    const Vector2f &Entity::getPosition() const {
        return _position;
    }

    void Entity::setPosition(const Vector2f &position) {
        _position = position;
    }

    const Vector2f &Entity::getScale() const {
        return _scale;
    }

    void Entity::setScale(const Vector2f &scale) {
        _scale = scale;
    }

    const float &Entity::getRotation() const {
        return _rotation;
    }

    void Entity::setRotation(const float &rotation) {
        _rotation = rotation;
    }

    void Entity::setView(std::shared_ptr<IEntityView> view) {
        _view = std::move(view);
    }

} // engine