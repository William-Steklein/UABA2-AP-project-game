#include "game/Game.h"
#include "game/state/MenuState.h"
#include "game/state/DebugState.h"
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
              _mouse_position(std::make_shared<engine::Vector2f>()) {
        loadResources();
        _config = parseConfig("data/config_default.json");

        _level_data = levelsDataParser("data/levels/levels.json");


        pushState(std::move(std::make_shared<MenuState>(*this)));
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

            getState()->handleInput(input_event);
        }
    }

    const std::shared_ptr<engine::Vector2f> &Game::getMousePosition() const {
        return _mouse_position;
    }

    void Game::setState(const std::shared_ptr<IGameState> &state) {
        if (state != nullptr) {
            if (!_states.empty()) {
                getState()->exit();
                _states.pop();
            }

            pushState(state);
        }
    }

    void Game::pushState(const std::shared_ptr<IGameState> &state) {
        if (!_states.empty()) {
            getState()->pause();
        }
        _states.push(state);

        getState()->enter();
        graphicsUpdateState();
    }

    void Game::popState() {
        if (_states.empty()) {
            throw std::runtime_error("Popping an empty game state stack");
        } else if (_states.size() == 1) {
            throw std::runtime_error("Popping last game state from stack");
        }
        getState()->exit();
        _states.pop();
        getState()->resume();
    }

    void Game::popAndSetState(const std::shared_ptr<IGameState> &state) {
        popState();
        setState(state);
    }

    void Game::popAndResetState() {
        popState();

        getState()->reset();
        graphicsUpdateState();
    }

    std::shared_ptr<IGameState> Game::getState() const {
        return _states.top();
    }

    const std::vector<std::shared_ptr<LevelData>> &Game::getLevelData() const {
        return _level_data;
    }

    void Game::graphicsUpdate(double t, float dt) {
        getState()->graphicsUpdate(t, dt);

        Engine::graphicsUpdate(t, dt);
    }

    void Game::graphicsUpdateState() const {
        getState()->graphicsUpdate(engine::Stopwatch::getInstance().getTime(),
                                   engine::Stopwatch::getInstance().getDeltaTime());
    }

    void Game::physicsUpdate(double t, float dt) {
        getState()->physicsUpdate(t, dt);

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