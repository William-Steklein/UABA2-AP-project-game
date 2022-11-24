#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <memory>
#include <utility>

#include "engine/entity/components/Transform.h"
#include "engine/entity/components/view/IViewComponent.h"
#include "engine/entity/components/animation/AnimationComponent.h"
#include "engine/entity/components/audio/IAudioComponent.h"

namespace engine {

    class Entity {
    public:
        Entity(const Transform &transform,
               std::shared_ptr<IViewComponent> view = nullptr,
               std::shared_ptr<AnimationComponent> animation = nullptr,
               std::shared_ptr<IAudioComponent> audio = nullptr);

        ~Entity();

        virtual void update(double t, float dt);

        const Transform &getTransform() const;

        void setTransform(const Transform &transform);

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        const Vector2f &getScale() const;

        void setScale(const Vector2f &scale);

        const float &getRotation() const;

        void setRotation(const float &rotation);

        void setViewComponent(std::shared_ptr<IViewComponent> component);

        void setAnimationComponent(std::shared_ptr<AnimationComponent> component);

        void setAudioComponent(std::shared_ptr<IAudioComponent> component);

//        void setPhysicsComponent(std::shared_ptr<PhysicsComponent> component);

        void checkComponent(const std::shared_ptr<IComponent> &component);

    protected:
        Transform _transform;

        // components
        std::shared_ptr<IViewComponent> _view;
        std::shared_ptr<AnimationComponent> _animation;
        std::shared_ptr<IAudioComponent> _audio;
        // - physics
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
