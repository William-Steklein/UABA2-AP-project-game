#include "game/Game.h"

namespace game {
    Game::Game(std::shared_ptr<engine::IResourceManager> resource_manager) : Engine(std::move(resource_manager)) {
        _resource_manager->loadAnimationResourceGroups(
                engine::parse_animation_info("data/resource-info/animations.json"));

        std::shared_ptr<engine::Entity> new_entity = std::make_shared<engine::Entity>(engine::Entity());
//        new_entity.addAudioComponent = ;
//        new_entity.addPhysicsComponent = ;
//        new_entity.addViewComponent = ;
    }

    Game::~Game() = default;

    void Game::update() {
        Engine::update();
    }

    void Game::update(double t, float dt) {
        Engine::update(t, dt);
    }

    void Game::physicsUpdate(double t, float dt) {
        Engine::physicsUpdate(t, dt);
    }
} // game