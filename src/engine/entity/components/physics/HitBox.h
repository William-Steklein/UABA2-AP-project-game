#ifndef GAME_ENGINE_HITBOX_H
#define GAME_ENGINE_HITBOX_H


#include "engine/entity/components/IComponent.h"

namespace engine {

    class HitBox : public IComponent {
    public:
        HitBox(const Vector2f &size, const Vector2f &offset = {});

        ~HitBox() = default;

        void update(double t, float dt) override;

        const Vector2f &getSize() const;

        void setSize(const Vector2f &size);

        Vector2f getScaledSize();

        const Vector2f &getOffset() const;

        void setOffset(const Vector2f &offset);

        bool collides(const Vector2f &point);

        bool collides(HitBox &other);

        Vector2f getDisplacementToCollision(HitBox &other);

    private:
        Vector2f _size;
    };

} // engine

#endif //GAME_ENGINE_HITBOX_H
