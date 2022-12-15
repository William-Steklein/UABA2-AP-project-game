#ifndef GAME_ENGINE_RAY_H
#define GAME_ENGINE_RAY_H


#include "engine/entity/components/physics/HitBox.h"

namespace engine {

    class Ray : public IComponent {
    public:
        Ray(const Vector2f &origin, const Vector2f &end);

        Ray(const Vector2f &origin, const Vector2f &direction, float length);

        ~Ray() override = default;

        void update(double t, float dt) override;

        const Vector2f &getOrigin() const;

        Vector2f getAbsoluteOrigin();

        void setOrigin(const Vector2f &origin);

        const Vector2f &getEnd() const;

        Vector2f getAbsoluteEnd();

        void setEnd(const Vector2f &end);

        bool collided() const;

        void setCollided(bool collided);

        const Vector2f &getCollisionPoint() const;

        void setCollisionPoint(const Vector2f &collision_point);

        void reset();

        bool collides(const Vector2f &other_absolute_origin, const Vector2f &other_absolute_end,
                      bool set_collision_point = true);

        bool collides(Ray &other, bool set_collision_point = true);

        bool collides(HitBox &other, bool set_collision_point = true);

    private:
        Vector2f _origin;
        Vector2f _end;

        bool _collided;
        Vector2f _collision_point;
    };

} // engine

#endif //GAME_ENGINE_RAY_H
