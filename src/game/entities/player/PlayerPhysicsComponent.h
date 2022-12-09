#ifndef GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H
#define GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H


#include <engine/entity/components/physics/PhysicsComponent.h>

#include "game/constants/constants.h"

namespace game {

    class PlayerPhysicsComponent : public engine::PhysicsComponent {
    public:
        PlayerPhysicsComponent(float jump_dt = constants::player::jump_dt,
                               float jump_height = constants::player::jump_height);

        ~PlayerPhysicsComponent() override = default;

        void update(double t, float dt) override;

        void applyGravityForce();

        void applyHorizontalMovementForce(bool left);

        void jump();

    private:
        engine::Vector2f _gravitational_acceleration;
        float _initial_jump_velocity;
        float _horizontal_movement_force;
    };

} // game

#endif //GAME_ENGINE_PLAYERPHYSICSCOMPONENT_H
