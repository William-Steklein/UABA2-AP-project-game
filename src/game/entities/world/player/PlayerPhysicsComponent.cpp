#include "PlayerPhysicsComponent.h"

namespace game {
    PlayerPhysicsComponent::PlayerPhysicsComponent()
            : engine::PhysicsComponent(false),
              _horizontal_movement_force(constants::player::horizontal_movement_force),
              _initial_jump_velocity(constants::player::initial_jump_velocity),
              _wall_horizontal_jump_velocity(constants::player::wall_horizontal_jump_velocity),
              _gravitational_acceleration(constants::player::gravitational_acceleration),
              _wall_vertical_velocity_cap(constants::player::wall_vertical_velocity_cap),
              _wall_velocity_clamp(false),
              _stopping_friction(constants::player::stopping_friction),
              _sliding_friction(constants::player::sliding_friction) {
        _mass = constants::player::mass;
        _horizontal_velocity_cap = constants::player::horizontal_velocity_cap;
        _vertical_velocity_cap = constants::player::vertical_velocity_cap;
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