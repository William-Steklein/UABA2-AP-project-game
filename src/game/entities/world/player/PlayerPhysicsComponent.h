#ifndef GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H
#define GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H


#include "engine/entity/components/physics/PhysicsComponent.h"
#include "engine/math/math_utils.h"

#include "game/constants/constants.h"

namespace game {

    class PlayerPhysicsComponent : public engine::PhysicsComponent {
    public:
        PlayerPhysicsComponent(float jump_dt = constants::player::jump_dt,
                               float jump_height = constants::player::jump_height);

        ~PlayerPhysicsComponent() override = default;

        void update(double t, float dt) override;

        void applyGravityForce(float multiply = 1.f);

        void applyHorizontalMovementForce(bool left);

        void jump(bool left = false);

        void walljump(bool left = false);

        void applyStoppingFrictionForce();

        void setWallVelocityClamp(bool wall_velocity_clamp);

    private:
        engine::Vector2f _gravitational_acceleration;
        float _initial_jump_velocity;
        float _wall_horizontal_jump_velocity;
        float _horizontal_movement_force;

        float _stopping_friction;

        bool _wall_velocity_clamp;
        engine::Vector2f _wall_vertical_velocity_cap;

        void clampVelocity() override;
    };

} // game

#endif //GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H
