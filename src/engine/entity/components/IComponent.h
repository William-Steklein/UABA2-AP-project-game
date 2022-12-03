#ifndef GAME_ENGINE_ICOMPONENT_H
#define GAME_ENGINE_ICOMPONENT_H


#include <memory>
#include <utility>

#include "engine/entity/Transform.h"

namespace engine {

    class Entity;

    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual void update(double t, float dt, Transform &transform) = 0;
    };

} // engine


#endif //GAME_ENGINE_ICOMPONENT_H
