#ifndef GAME_ENGINE_ICOMPONENT_H
#define GAME_ENGINE_ICOMPONENT_H


#include <memory>
#include <utility>

#include "engine/entity/Transform.h"

namespace engine {

    class IComponent {
    public:
        IComponent() {}

        virtual ~IComponent() = default;

        void setTransform(std::weak_ptr<Transform> transform) {_transform = std::move(transform);}

        std::shared_ptr<Transform> getTransform() {
            if (_transform.expired()) {
                throw std::runtime_error("Component has no transform");
            }
            return _transform.lock();
        }

        virtual void update(double t, float dt) = 0;

    protected:
        std::weak_ptr<Transform> _transform;
    };

} // engine


#endif //GAME_ENGINE_ICOMPONENT_H
