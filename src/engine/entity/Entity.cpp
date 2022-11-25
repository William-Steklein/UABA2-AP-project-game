#include "engine/entity/Entity.h"

namespace engine {
    Entity::Entity(const Transform &transform,
                   std::shared_ptr<IViewComponent> view,
                   std::shared_ptr<AnimationComponent> animation,
                   std::shared_ptr<IAudioComponent> audio)
            : _transform(transform),
              _view(std::move(view)), _animation(std::move(animation)), _audio(std::move(audio)) {
        // link animation and view
        if (_animation.get()) {
            if (_animation->getView().get()) {
                _view = _animation->getView();
            } else {
                _animation->setView(_view);
            }
        }
    }

    Entity::~Entity() = default;

    void Entity::update(double t, float dt) {
        for (const auto &component: std::vector<std::shared_ptr<IComponent>>{_animation, _view}) {
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

    void Entity::setViewComponent(std::shared_ptr<IViewComponent> component) {
        if (component.get()) {
            _view = std::move(component);
        } else {
            throw std::runtime_error("Setting an empty view component to entity");
        }
    }

    void Entity::setAnimationComponent(std::shared_ptr<AnimationComponent> component) {
        if (component.get()) {
            _animation = std::move(component);
        } else {
            throw std::runtime_error("Setting an empty animation component to entity");
        }
    }

    void Entity::setAudioComponent(std::shared_ptr<IAudioComponent> component) {
        if (component.get()) {
            _audio = std::move(component);
        } else {
            throw std::runtime_error("Setting an empty audio component to entity");
        }
    }

    void Entity::checkComponent(const std::shared_ptr<IComponent> &component) {
        if (!component.get()) {
            throw std::runtime_error("Entity was initialized with an empty component");
        }
    }
} // engine