#ifndef GAME_ENGINE_ICOMPONENT_H
#define GAME_ENGINE_ICOMPONENT_H


#include <memory>
#include <utility>

namespace engine {

    class Entity;

    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual void update(double t, float dt, Entity &entity) = 0;
    };

} // engine


#endif //GAME_ENGINE_ICOMPONENT_H
