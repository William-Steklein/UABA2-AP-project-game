#include "PlayerPhysicsComponent.h"

namespace game {
    PlayerPhysicsComponent::PlayerPhysicsComponent(float jump_dt, float jump_height)
            : engine::PhysicsComponent(false) {
        _mass = constants::player::mass;
        _initial_jump_velocity = 2 * jump_height / jump_dt;
        _wall_horizontal_jump_velocity = _initial_jump_velocity * 0.75f;
        _horizontal_movement_force = constants::player::horizontal_movement_force;

        _gravitational_acceleration = {0, -2 * jump_height / (jump_dt * jump_dt)};

        _horizontal_velocity_cap = {-3.5f, 3.5f};
        _vertical_velocity_cap = {-_initial_jump_velocity * 1.25f, _initial_jump_velocity * 1.25f};

        _stopping_friction = 250.f;
        _sliding_friction = 50.f;

        _wall_velocity_clamp = false;
        _wall_vertical_velocity_cap = {-_initial_jump_velocity * 0.5f, _initial_jump_velocity * 0.5f};
    }

    void PlayerPhysicsComponent::update(double t, float dt) {
        PhysicsComponent::update(t, dt);
    }

    void PlayerPhysicsComponent::applyGravityForce(float multiply) {
        _acceleration += _gravitational_acceleration * multiply;
    }

    void PlayerPhysicsComponent::applyHorizontalMovementForce(bool left) {
        if (left) {
            addForce({-_horizontal_movement_force, 0});
        } else {
            addForce({_horizontal_movement_force, 0});
        }
    }

    void PlayerPhysicsComponent::jump(bool left) {
        addVelocity({0, _initial_jump_velocity});
    }

    void PlayerPhysicsComponent::walljump(bool left) {
        if (left) {
            addVelocity({-_wall_horizontal_jump_velocity, _initial_jump_velocity});
        } else {
            addVelocity({_wall_horizontal_jump_velocity, _initial_jump_velocity});
        }
    }

    void PlayerPhysicsComponent::applyStoppingFrictionForce() {
        if (_velocity.x == 0) {
            return;
        }

        addForce({_velocity.x * -_stopping_friction, 0});
    }

    void PlayerPhysicsComponent::applyWallSlidingFrictionForce() {
        if (_velocity.y <= 0) {
            return;
        }

        addForce({0, _velocity.y * -_sliding_friction});
    }

    void PlayerPhysicsComponent::clampVelocity() {
        if (_wall_velocity_clamp) {
            _velocity.y = engine::clamp(_velocity.y, _wall_vertical_velocity_cap.x, _wall_vertical_velocity_cap.y);
        } else {
            PhysicsComponent::clampVelocity();
        }
    }

    void PlayerPhysicsComponent::setWallVelocityClamp(bool wall_velocity_clamp) {
        _wall_velocity_clamp = wall_velocity_clamp;
    }
} // game