#include "PlayerPhysicsComponent.h"

namespace game {
    PlayerPhysicsComponent::PlayerPhysicsComponent(float jump_dt, float jump_height) : engine::PhysicsComponent(false) {
        _mass = constants::player::mass;
        _initial_jump_velocity = 2 * jump_height / jump_dt;
        _horizontal_movement_force = constants::player::horizontal_movement_force;

        _gravitational_acceleration = {0, -2 * jump_height / (jump_dt * jump_dt)};

//        _min_neg_velocity = {-1.5f, -(_initial_jump_velocity * 1.5f)};
//        _max_pos_velocity = {1.5f, constants::player::jump_velocity * 5.f};
//        _drag = {0.15f, 0};
//        _friction = {5.f, 0};
    }

    void PlayerPhysicsComponent::update(double t, float dt) {
        PhysicsComponent::update(t, dt);
    }

    void PlayerPhysicsComponent::applyGravityForce() {
        _acceleration += _gravitational_acceleration;
    }

    void PlayerPhysicsComponent::applyHorizontalMovementForce(bool left) {
        if (left) {
            addForce({-_horizontal_movement_force, 0});
        } else {
            addForce({_horizontal_movement_force, 0});
        }
    }

    void PlayerPhysicsComponent::jump() {
        addVelocity({0, _initial_jump_velocity});
    }
} // game