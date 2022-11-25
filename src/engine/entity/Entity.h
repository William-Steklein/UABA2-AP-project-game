#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <memory>
#include <utility>

#include "engine/entity/components/Transform.h"
#include "engine/entity/components/view/ISpriteComponent.h"
#include "engine/entity/components/view/IAnimatedSpriteComponent.h"
#include "engine/entity/components/audio/IAudioComponent.h"

namespace engine {

    class Entity {
    public:
        Entity(const Transform &transform);

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

        static void checkComponent(const std::shared_ptr<IComponent> &component);

    protected:
        Transform _transform;

        std::vector<std::shared_ptr<IComponent>> _components;

        // components
//        std::shared_ptr<IViewComponent> _view;
//        std::shared_ptr<AnimationComponent> _animation;
//        std::shared_ptr<IAudioComponent> _audio;
        // - physics
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
