#include "game/Game.h"

namespace game {
    Game::Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
               std::shared_ptr<engine::IResourceManager> resource_manager,
               std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
               std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator,
               std::shared_ptr<IGameState> start_state)
            : Engine(screen_x_min, screen_x_max, screen_y_min, screen_y_max,
                     std::move(resource_manager),
                     std::move(view_component_creator),
                     std::move(audio_component_creator)),
              _state(std::move(start_state)) {
        loadResources();
        _config = parseConfig("data/config_default.json");

        _state->enter(*this);

//        _player = std::make_shared<Player>(Player(
//                {{0, 0}, {1, 1}, 0},
//                std::make_shared<IdleState>(),
//                _view_component_creator->createAnimatedSprite({0.8f, 0.56f}, 0, "adventurer")
//        ));
//
//        _physics_entities.insert(_player);

//        std::shared_ptr<Explosion> new_entity = std::make_shared<Explosion>(Explosion(
//                {{0, 0}, {1, 1}, 0},
//                _view_component_creator->createAnimatedSprite({1, 1}, 0, "explosion"),
//                _audio_component_creator->create()
//        ));
//        _physics_entities.insert(new_entity);
//
//        std::shared_ptr<UIWidget> new_ui_widget = std::make_shared<UIWidget>(UIWidget(
//                {{-0.25f, 0.25f}, {1, 1}, 0},
//                _view_component_creator->createSprite({1.f, 0.5f}, 1, "button"),
//                _view_component_creator->createRectangle({1.f, 0.5f}, 2),
//                _view_component_creator->createTextBox({1.f, 0.5f}, 3, "PTSans-regular")
//                ));
//
//        _entities.insert(new_ui_widget);
    }

    void Game::update() {
        Engine::update();
    }

    void Game::handleInputs(const std::vector<engine::Input> &inputs) {
        for (const auto &input: inputs) {
            if (input.type == engine::Input::InputType::MOUSEMOVED ||
                _config.button_map.keyboard.find(input.button) == _config.button_map.keyboard.end()) {
                continue;
            }

            game::InputEvent event{};
            event.type = _config.button_map.keyboard.at(input.button);
            event.state_enter = input.type == engine::Input::InputType::KEYPRESSED;

            std::shared_ptr<IGameState> state = _state->handleInput(*this, event);

            if (state != nullptr) {
                _state = state;
                _state->enter(*this);
            }
        }
    }

    void Game::update(double t, float dt) {
        _state->update(*this, t, dt);

        Engine::update(t, dt);
    }

    void Game::physicsUpdate(double t, float dt) {
        _state->physicsUpdate(*this, t, dt);

        Engine::physicsUpdate(t, dt);
    }

    void Game::loadResources() {
        _resource_manager->loadTextureResources(engine::parseTextureInfo("data/resource-info/textures.json"));
        _resource_manager->loadAnimationResourceGroups(
                engine::parseAnimationInfo("data/resource-info/animations.json"));
        _resource_manager->loadSoundResources(engine::parseAudioInfo("data/resource-info/sounds.json"));
        _resource_manager->loadMusicResources(engine::parseAudioInfo("data/resource-info/music.json"));
        _resource_manager->loadFontResources(engine::parseFontInfo("data/resource-info/fonts.json"));
    }
} // game