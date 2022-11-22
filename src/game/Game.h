#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <engine/Engine.h>
#include <engine/entities/Entity.h>
#include <engine/entities/components/EntityAnimation.h>
#include "game/entities/Explosion.h"

namespace game {

    class Game : public engine::Engine {
    public:
        Game(std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IEntityViewCreator> entity_view_creator);

        ~Game();

        void update() override;

    private:
        void update(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadResources();
    };

} // game


#endif //GAME_ENGINE_GAME_H
