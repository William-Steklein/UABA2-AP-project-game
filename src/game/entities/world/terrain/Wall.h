#ifndef GAME_ENGINE_WALL_H
#define GAME_ENGINE_WALL_H


#include "engine/entity/Entity.h"
#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/entity/components/physics/PhysicsComponent.h"

namespace game {

    class Wall : public engine::Entity {
    public:
        Wall(engine::Transform transform, const engine::Vector2f &size);

        std::shared_ptr<engine::PhysicsComponent> getPhysicsComponent();

    private:
        std::shared_ptr<engine::PhysicsComponent> _physics_component;
    };

} // game

#endif //GAME_ENGINE_WALL_H
