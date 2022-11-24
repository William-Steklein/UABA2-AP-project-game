#include "game/Game.h"

namespace game {
    Game::Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
               std::shared_ptr<engine::IResourceManager> resource_manager,
               std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
               std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator)
            : Engine(screen_x_min, screen_x_max, screen_y_min, screen_y_max,
                     std::move(resource_manager),
                     std::move(view_component_creator),
                     std::move(audio_component_creator)) {
        loadResources();

        std::shared_ptr<Explosion> new_entity = std::make_shared<Explosion>(Explosion(
                {{0, 0}, {1, 1}, 0},
                _animation_component_creator->create("explosion", 0),
                _audio_component_creator->create()
        ));
        _physics_entities.insert(new_entity);

        std::shared_ptr<Player> player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                nullptr,
                nullptr,
                _audio_component_creator->create()
        ));
        _physics_entities.insert(player);

        _audio_component_creator->setChannelVolume(1, 25);
        _audio_component_creator->setChannelVolume(0, 100);
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
        _resource_manager->loadSoundResources(engine::parseAudioInfo("data/resource-info/sounds.json"));
        _resource_manager->loadMusicResources(engine::parseAudioInfo("data/resource-info/music.json"));
    }
} // game