#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <memory>
#include <utility>

#include "engine/entities/components/Transform.h"
#include "engine/entities/components/IEntityView.h"
#include "engine/entities/components/EntityAnimation.h"

namespace engine {

    class Entity {
    public:
        Entity(const Transform &transform,
               std::shared_ptr<IEntityView> view = nullptr, std::shared_ptr<EntityAnimation> animation = nullptr);

        ~Entity();

        virtual void update(double t, float dt);

        const Transform &getTransform() const;

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        const Vector2f &getScale() const;

        void setScale(const Vector2f &scale);

        const float &getRotation() const;

        void setRotation(const float &rotation);

        void setViewComponent(std::shared_ptr<IEntityView> view);

        void setAnimationComponent(std::shared_ptr<EntityAnimation> animation);

//        void setAudioComponent(std::shared_ptr<IEntityAudio> audio);

//        void setRigidBodyComponent(std::shared_ptr<EntityRigidBody> rigid_body);

        void checkComponent(const std::shared_ptr<IEntityComponent> &component);

    protected:
        Transform _transform;

        // components
        std::shared_ptr<IEntityView> _view;
        std::shared_ptr<EntityAnimation> _animation;
        // - audio
        // - rigidbody (physics)
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
