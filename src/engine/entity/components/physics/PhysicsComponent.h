#ifndef GAME_ENGINE_PHYSICSCOMPONENT_H
#define GAME_ENGINE_PHYSICSCOMPONENT_H


#include "engine/entity/components/IComponent.h"
#include "HitBox.h"

namespace engine {

    class PhysicsComponent : public IComponent {
    public:
        PhysicsComponent(bool is_static = true);

        ~PhysicsComponent() override = default;

        /**
         * Physics integration, reference "https://gafferongames.com/post/integration_basics/"
         * @param t
         * @param dt
         */
        void update(double t, float dt) override;

        float getMass() const;

        void setMass(float mass);

        const Vector2f &getForce() const;

        void setForce(const Vector2f &force);

        void addForce(const Vector2f &force);

        const Vector2f &getVelocity() const;

        void setVelocity(const Vector2f &velocity);

        void addVelocity(const Vector2f &velocity);

        const Vector2f &getAcceleration() const;

        void setAcceleration(const Vector2f &acceleration);

        const std::shared_ptr<HitBox> &getHitBox() const;

        void setHitBox(const std::shared_ptr<HitBox> &hitBox);

        bool isIsStatic() const;

        void setIsStatic(bool is_static);

        bool isCollided() const;

        void setCollided(bool collided);

        void handleCollision(PhysicsComponent &other, bool resolve = true, bool set_collided = true);

    protected:
        float _mass;
        Vector2f _force;
        Vector2f _velocity;
        Vector2f _acceleration;

        engine::Vector2f _horizontal_velocity_cap;
        engine::Vector2f _vertical_velocity_cap;

        std::shared_ptr<HitBox> _hit_box;

        bool _is_static;
        bool _collided;

        void resolveCollision(PhysicsComponent &other);

        virtual void clampVelocity();
    };

} // engine

#endif //GAME_ENGINE_PHYSICSCOMPONENT_H
