#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H


#include <memory>
#include <set>
#include <utility>

#include "engine/Stopwatch.h"
#include "engine/logging/Logger.h"
#include "engine/entities/Entity.h"
#include "engine/resources/IResourceManager.h"
#include "engine/entities/IEntityViewCreator.h"

namespace engine {

    class Engine {
    public:
        Engine(std::shared_ptr<IResourceManager> resource_manager,
               std::shared_ptr<IEntityViewCreator> entity_view_creator);

        ~Engine();

        static void sleep();

        virtual void update();

    protected:
        std::set<std::shared_ptr<Entity>> _entities;
        std::set<std::shared_ptr<Entity>> _physics_entities;

        std::shared_ptr<IResourceManager> _resource_manager;
        std::shared_ptr<IEntityViewCreator> _entity_view_creator;

        virtual void update(double t, float dt);

        virtual void physicsUpdate(double t, float dt);

    private:
        float _physics_delta_time;
        double _physics_time;
        float _accumulator;
        float _physics_speed;
    };

} // engine

#endif //GAME_ENGINE_ENGINE_H
