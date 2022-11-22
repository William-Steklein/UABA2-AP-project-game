#include "game/Game.h"

namespace game {

    Game::Game(std::shared_ptr<engine::IResourceManager> resource_manager,
               std::shared_ptr<engine::IEntityViewCreator> entity_view_creator)
            : Engine(std::move(resource_manager), std::move(entity_view_creator)) {
        loadResources();

//        std::shared_ptr<engine::Entity> new_entity = std::make_shared<engine::Entity>(engine::Entity(
//                _entity_view_creator->create(0, "explosion"),
//                std::make_shared<engine::EntityAnimation>(_resource_manager->getAnimationGroup("explosion"))
//        ));
        std::shared_ptr<Explosion> new_entity = std::make_shared<Explosion>(Explosion(
                _entity_view_creator->create(0, "explosion"),
                std::make_shared<engine::EntityAnimation>(_resource_manager->getAnimationGroup("explosion"))
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