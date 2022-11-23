#include "game/Game.h"

namespace game {
    Game::Game(std::shared_ptr<engine::IResourceManager> resource_manager,
               std::shared_ptr<engine::IViewComponentCreator> entity_view_creator)
            : Engine(std::move(resource_manager), std::move(entity_view_creator)) {
        loadResources();

//        std::shared_ptr<engine::Entity> new_entity = std::make_shared<engine::Entity>(engine::Entity(
//                {{0, 0}, {1, 1}, 0},
//                _entity_view_creator->create("explosion", 0)
//        ));
        std::shared_ptr<Explosion> new_entity = std::make_shared<Explosion>(Explosion(
                {{0, 0}, {1, 1}, 0},
                _entity_animation_creator->create("explosion", 0)
        ));
        _physics_entities.insert(new_entity);
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

    void Game::loadResources() {
        _resource_manager->loadTextureResources(engine::parseTextureInfo("data/resource-info/textures.json"));
        _resource_manager->loadAnimationResourceGroups(
                engine::parseAnimationInfo("data/resource-info/animations.json"));
        _resource_manager->loadAudioResources(engine::parseAudioInfo("data/resource-info/audio.json"));
    }
} // game