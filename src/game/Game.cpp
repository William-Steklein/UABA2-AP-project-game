#include "game/Game.h"
#include "game/constants/constants.h"
#include "game/state/menu/MainMenuState.h"
#include "game/level/level_data_parser.h"

namespace game {
    Game::Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
               std::shared_ptr<engine::IResourceManager> resource_manager,
               std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
               std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator)
            : Engine(screen_x_min, screen_x_max, screen_y_min, screen_y_max,
                     std::move(resource_manager),
                     std::move(view_component_creator),
                     std::move(audio_component_creator)),
              _mouse_position(std::make_shared<engine::Vector2f>()),
              _current_level_id(0) {
        initSidebars(constants::layer::side_bar);
        loadResources();
        _config = parseConfig("data/config_default.json");

        _level_data = levelsDataParser("data/levels/levels.json");

        IGameState::init<MainMenuState>(*this, _states);
    }

    void Game::update() {
        Engine::update();
    }

    void Game::handleInputs(const std::vector<engine::Input> &inputs) {
        for (const auto &input: inputs) {
            game::InputEvent input_event{};

            if (input.type == engine::Input::InputType::MOUSEMOVED) {
                // mouse move
                input_event.type = game::InputEvent::Type::MOUSEMOVED;

                _mouse_position->x = input.range_2d.x;
                _mouse_position->y = input.range_2d.y;
                *_mouse_position = _camera->projectCoordSubScreenToWorld(*_mouse_position);
            } else if (input.button == engine::Input::Button::MOUSELEFT) {
                // mouse buttonpress
                input_event.type = game::InputEvent::Type::MOUSECLICK;
                input_event.state = mapEngineToGameInput(input.type);
            } else {
                // keyboard buttonpress

                // if unable to map to game input event
                if (_config.button_map.keyboard.find(input.button) == _config.button_map.keyboard.end()) {
                    continue;
                }

                input_event.type = _config.button_map.keyboard.at(input.button);
                input_event.state = mapEngineToGameInput(input.type);
            }
            input_event.range = 0;

            _states.top()->handleInput(input_event);
        }
    }

    const std::shared_ptr<engine::Vector2f> &Game::getMousePosition() const {
        return _mouse_position;
    }

    void Game::setCurrentLevelId(unsigned int level_id) {
        if (level_id >= _level_data.size()) {
            throw std::runtime_error("No level with id \"" + std::to_string(level_id) + "\"");
        }

        _current_level_id = level_id;
    }

    const std::vector<std::shared_ptr<LevelData>> &Game::getLevelData() const {
        return _level_data;
    }

    const std::shared_ptr<LevelData> &Game::getLevelDataPoint(unsigned int level_id) const {
        return _level_data[level_id];
    }

    const std::shared_ptr<LevelData> &Game::getCurrentLevelDataPoint() const {
        return _level_data[_current_level_id];
    }

    bool Game::isLastLevel() const {
        return _current_level_id == _level_data.size() - 1;
    }

    void Game::advanceCurrentLevel() {
        if (isLastLevel()) {
            _current_level_id = 0;
        } else {
            _current_level_id++;
        }
    }

    void Game::graphicsUpdate(double t, float dt) {
        _states.top()->graphicsUpdate(t, dt);

        Engine::graphicsUpdate(t, dt);
    }

    void Game::physicsUpdate(double t, float dt) {
        _states.top()->physicsUpdate(t, dt);

        Engine::physicsUpdate(t, dt);
    }

    void Game::loadResources() {
        _resource_manager->loadTextureResources(engine::parseTextureInfo("data/resource-info/textures.json"));
        _resource_manager->loadAnimationResources(engine::parseAnimationInfo("data/resource-info/animations.json"));
        _resource_manager->loadSoundResources(engine::parseAudioInfo("data/resource-info/sounds.json"));
        _resource_manager->loadMusicResources(engine::parseAudioInfo("data/resource-info/music.json"));
        _resource_manager->loadFontResources(engine::parseFontInfo("data/resource-info/fonts.json"));
    }
} // game