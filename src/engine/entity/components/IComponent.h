#ifndef GAME_ENGINE_ICOMPONENT_H
#define GAME_ENGINE_ICOMPONENT_H


#include <memory>
#include <utility>

#include "engine/entity/Transform.h"

namespace engine {

    class IComponent {
    public:
        IComponent() = default;

        virtual ~IComponent() = default;

        std::shared_ptr<Transform> getTransform();

        void setTransform(std::weak_ptr<Transform> transform);

        const Transform &getRelativeTransform() const;

        void setRelativeTransform(const Transform &relativeTransform);

        virtual Vector2f getPosition();

        virtual Vector2f getScale();

        virtual float getRotation();

        virtual void update(double t, float dt) = 0;

    protected:
        std::weak_ptr<Transform> _transform;
        Transform _relative_transform;
    };

} // engine


#endif //GAME_ENGINE_ICOMPONENT_H
