#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <engine/Engine.h>
#include <engine/entity/Entity.h>
#include <engine/entity/components/animation/AnimationComponent.h>

#include "game/entities/Explosion.h"

namespace game {

    class Game : public engine::Engine {
    public:
        Game(std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IViewComponentCreator> view_component_creator);

        ~Game();

        void update() override;

    private:
        void update(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadResources();
    };

} // game


#endif //GAME_ENGINE_GAME_H
