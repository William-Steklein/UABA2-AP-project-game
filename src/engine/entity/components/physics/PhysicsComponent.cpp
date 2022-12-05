#include "PhysicsComponent.h"
#include "engine/logging/Logger.h"

namespace engine {
    PhysicsComponent::PhysicsComponent(bool is_static)
            : _mass(1),
              _hit_box(std::make_shared<HitBox>(HitBox({0, 0}, {0, 0}))),
              _is_static(is_static), _collided(false) {

    }

    void PhysicsComponent::update(double t, float dt) {
        std::shared_ptr<Transform> transform = getTransform();

        if (_is_static) return;

        // force acceleration
        _acceleration += _force / _mass;

        // position(t): position + velocity * timestep + (acceleration / 2 * timestep^2)
        transform->move(_velocity * dt + _acceleration / 2 * dt * dt);
        // verlet integration
        _velocity += _acceleration * dt;

        // clear force and acceleration
        _force = {0, 0};
        _acceleration = {0, 0};
    }

    float PhysicsComponent::getMass() const {
        return _mass;
    }

    void PhysicsComponent::setMass(float mass) {
        _mass = mass;
    }

    const Vector2f &PhysicsComponent::getForce() const {
        return _force;
    }

    void PhysicsComponent::setForce(const Vector2f &force) {
        _force = force;
    }

    void PhysicsComponent::addForce(const Vector2f &force) {
        _force += force;
    }

    const Vector2f &PhysicsComponent::getVelocity() const {
        return _velocity;
    }

    void PhysicsComponent::setVelocity(const Vector2f &velocity) {
        _velocity = velocity;
    }

    void PhysicsComponent::addVelocity(const Vector2f &velocity) {
        _velocity += velocity;
    }

    const Vector2f &PhysicsComponent::getAcceleration() const {
        return _acceleration;
    }

    void PhysicsComponent::setAcceleration(const Vector2f &acceleration) {
        _acceleration = acceleration;
    }

    void PhysicsComponent::setHitBox(const std::shared_ptr<HitBox> &hitBox) {
        _hit_box = hitBox;
    }

    bool PhysicsComponent::isIsStatic() const {
        return _is_static;
    }

    void PhysicsComponent::setIsStatic(bool is_static) {
        _is_static = is_static;
    }

    bool PhysicsComponent::isCollided() const {
        return _collided;
    }

    void PhysicsComponent::setCollided(bool collided) {
        _collided = collided;
    }

    const std::shared_ptr<HitBox> &PhysicsComponent::getHitBox() const {
        return _hit_box;
    }

    void PhysicsComponent::handleCollision(PhysicsComponent &other) {
        if (_hit_box->collides(*other.getHitBox())) {
            LOGDEBUG("collision!");
        }
    }
} // enginea