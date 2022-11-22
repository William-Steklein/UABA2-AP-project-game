#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <memory>
#include <utility>

#include "engine/math/Vector2f.h"
#include "engine/entities/components/IEntityView.h"
#include "engine/entities/components/EntityAnimation.h"

namespace engine {

    class Entity {
    public:
        Entity(std::shared_ptr<IEntityView> view, std::shared_ptr<EntityAnimation> animation);

        ~Entity();

        virtual void update(double t, float dt);

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        const Vector2f &getScale() const;

        void setScale(const Vector2f &scale);

        const float &getRotation() const;

        void setRotation(const float &rotation);

        void setView(std::shared_ptr<IEntityView> view);

    protected:
        // transform
        Vector2f _position;
        Vector2f _scale;
        float _rotation;

        // components
        std::shared_ptr<IEntityView> _view;
        std::shared_ptr<EntityAnimation> _animation;
        // - audio
        // - rigidbody (physics)
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
