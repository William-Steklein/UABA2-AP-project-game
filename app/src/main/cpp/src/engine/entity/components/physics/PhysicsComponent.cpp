#include "PhysicsComponent.h"
#include "engine/logging/Logger.h"
#include "engine/math/math_utils.h"
#include "engine/constants/constants.h"

namespace engine {
    PhysicsComponent::PhysicsComponent(bool is_static)
            : _mass(1),
              _hit_box(std::make_shared<HitBox>(HitBox({0, 0}, {0, 0}))),
              _is_static(is_static), _collided(false), _horizontal_velocity_cap({0, 0}),
              _vertical_velocity_cap({0, 0}) {

    }

    void PhysicsComponent::update(double t, float dt) {
        std::shared_ptr<Transform> transform = getTransform();

        if (_is_static) return;

        // force acceleration
        _acceleration += _force / _mass;

        // semi-implicit euler
        _velocity += _acceleration * dt;

        clampVelocity();

        transform->move(_velocity * dt);

        // remove small velocities
        if (_velocity.x < constants::velocity_epsilon && _velocity.x > -constants::velocity_epsilon)
            _velocity.x = 0;
        if (_velocity.y < constants::velocity_epsilon && _velocity.y > -constants::velocity_epsilon)
            _velocity.y = 0;

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

    void PhysicsComponent::handleCollision(PhysicsComponent &other, bool resolve, bool set_collided) {
        if (_hit_box->collides(*other.getHitBox())) {
            if (set_collided) {
                setCollided(true);
                other.setCollided(true);
            }

            if (resolve) {
                resolveCollision(other);
            }
        }
    }

    void PhysicsComponent::resolveCollision(PhysicsComponent &other) {
        Vector2f displacement = _hit_box->getDisplacementToCollision(*other.getHitBox());
        Vector2f move_vector;

        Vector2f new_velocity_this = _velocity;
        Vector2f new_velocity_other = other._velocity;

        if (std::abs(displacement.x) == std::abs(displacement.y)) {
            move_vector = {displacement.x, displacement.y};
        } else if (std::abs(displacement.x) < std::abs(displacement.y)) {
            move_vector = {displacement.x, 0};

            new_velocity_this.x = 0;
            new_velocity_other.x = 0;
        } else {
            move_vector = {0, displacement.y};

            new_velocity_this.y = 0;
            new_velocity_other.y = 0;
        }

        if (!_is_static && other._is_static) {
            // this is dynamic
            getTransform()->move(move_vector);
            _velocity = new_velocity_this;

        } else if (_is_static && !other._is_static) {
            // other is dynamic
            other.getTransform()->move(move_vector * -1);
            other._velocity = new_velocity_other;

        } else if (!_is_static && !other._is_static) {
            // both are dynamic
            float alpha;

            if (other._mass < _mass) {
                alpha = other._mass / _mass;
            } else {
                alpha = 1 - (_mass / other._mass);
            }

            getTransform()->move(lerp({0, 0}, move_vector, alpha));
            other.getTransform()->move(lerp({0, 0}, move_vector * -1, 1 - alpha));

            Vector2f new_velocity;

            if (_velocity.length() + other._velocity.length() < (_velocity + other._velocity).length()) {
                new_velocity = _velocity + other._velocity;
            } else {
                new_velocity = _velocity.length() > other._velocity.length() ? _velocity : other._velocity;
            }

            _velocity = new_velocity;
            other._velocity = new_velocity;
        } else {
            throw std::runtime_error("Collisions between two dynamic objects are not supported");
        }
    }

    void PhysicsComponent::clampVelocity() {
        _velocity = {engine::clamp(_velocity.x, _horizontal_velocity_cap.x, _horizontal_velocity_cap.y),
                     engine::clamp(_velocity.y, _vertical_velocity_cap.x, _vertical_velocity_cap.y)};
    }
} // enginea