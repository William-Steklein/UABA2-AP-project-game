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
              _mouse_position(std::make_shared<engine::Vector2f>()) {
        loadResources();
        _config = parseConfig("data/config_default.json");

        _states.push(std::move(start_state));
        _states.top()->enter(*this);
    }

    void Game::update() {
        Engine::update();
    }

    void Game::handleInputs(const std::vector<engine::Input> &inputs) {
        for (const auto &input: inputs) {
            game::InputEvent input_event{};

            if (input.type == engine::Input::InputType::MOUSEMOVED) {
                input_event.type = game::InputEvent::Type::MOUSEMOVED;

                _mouse_position->x = input.range_2d.x;
                _mouse_position->y = input.range_2d.y;
                *_mouse_position = _camera->projectCoordSubScreenToWorld(*_mouse_position);
            } else if (input.button == engine::Input::Button::MOUSELEFT) {
                // mouse buttonpress
                input_event.type = game::InputEvent::Type::MOUSECLICK;
                input_event.state_enter = input.type == engine::Input::InputType::MOUSEPRESSED;
            } else {
                // keyboard buttonpress

                // if unable to map to game input event
                if (_config.button_map.keyboard.find(input.button) == _config.button_map.keyboard.end()) {
                    continue;
                }

                input_event.type = _config.button_map.keyboard.at(input.button);
                input_event.state_enter = input.type == engine::Input::InputType::KEYPRESSED;
            }
            input_event.range = 0;

            getState()->handleInput(*this, input_event);
        }
    }

    const std::shared_ptr<engine::Vector2f> &Game::getMousePosition() const {
        return _mouse_position;
    }

    void Game::setState(const std::shared_ptr<IGameState> &state) {
        if (state != nullptr) {
            if (_states.empty()) {
                _states.push(state);
            } else {
                _states.pop();
                _states.push(state);
            }

            getState()->enter(*this);
        }
    }

    void Game::pushState(const std::shared_ptr<IGameState> &state) {
        _states.push(state);
        _states.top()->enter(*this);
    }

    void Game::popState() {
        if (_states.empty()) {
            throw std::runtime_error("Popping an empty game state stack");
        } else if (_states.size() == 1) {
            throw std::runtime_error("Popping last game state from stack");
        }
        _states.pop();
    }

    void Game::popAndSetState(const std::shared_ptr<IGameState> &state) {
        popState();
        setState(state);
    }

    void Game::popAndResetState() {
        popState();
        getState()->reset(*this);
    }

    std::shared_ptr<IGameState> Game::getState() const {
        return _states.top();
    }

    void Game::update(double t, float dt) {
        getState()->update(*this, t, dt);

        Engine::update(t, dt);
    }

    void Game::physicsUpdate(double t, float dt) {
        getState()->physicsUpdate(*this, t, dt);

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