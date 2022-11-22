#ifndef GAME_ENGINE_IENTITYCOMPONENT_H
#define GAME_ENGINE_IENTITYCOMPONENT_H


#include <memory>
#include <utility>

namespace engine {

    class Entity;

    class IEntityComponent {
    public:
        virtual void update(double t, float dt, Entity &entity) = 0;
    };

} // engine


#endif //GAME_ENGINE_IENTITYCOMPONENT_H
