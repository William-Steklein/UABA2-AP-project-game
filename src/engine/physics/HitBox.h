#ifndef GAME_ENGINE_HITBOX_H
#define GAME_ENGINE_HITBOX_H


#include "engine/math/Vector2f.h"

namespace engine {

    class HitBox {
    public:
        HitBox(const Vector2f &position, const Vector2f &size, const Vector2f &offset = {});

        ~HitBox() = default;

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        const Vector2f &getSize() const;

        void setSize(const Vector2f &size);

        const Vector2f &getOffset() const;

        void setOffset(const Vector2f &offset);

        bool collides(const Vector2f &point) const;

        bool collides(const HitBox &other) const;

    private:
        Vector2f _position;
        Vector2f _size;
        Vector2f _offset;
    };

} // engine

#endif //GAME_ENGINE_HITBOX_H
