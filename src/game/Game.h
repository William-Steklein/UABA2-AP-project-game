#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <engine/Engine.h>
#include <engine/entity/Entity.h>
#include <engine/entity/components/animation/AnimationComponent.h>

#include "game/entities/Player.h"
#include "game/entities/Explosion.h"
#include "game/entities/UIWidget.h"

namespace game {

    class Game : public engine::Engine {
    public:
        Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
             std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
             std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator);

        ~Game();

        void update() override;

    private:
        void update(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadResources();
    };

} // game


#endif //GAME_ENGINE_GAME_H
