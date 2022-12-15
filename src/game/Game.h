#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <stack>
#include <iostream>

#include <engine/Engine.h>

#include "game/input/InputEvent.h"
#include "game/config/config_parser.h"

namespace game {

    struct IGameState;

    class Game : public engine::Engine {
    public:
        Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
             std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
             std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator);

        ~Game() override = default;

        void update() override;

        // handles engine input and convert them to game input events
        void handleInputs(const std::vector<engine::Input> &inputs) override;

        const std::shared_ptr<engine::Vector2f> &getMousePosition() const;

        void setState(const std::shared_ptr<IGameState> &state);

        void pushState(const std::shared_ptr<IGameState> &state);

        void popState();

        void popAndSetState(const std::shared_ptr<IGameState> &state);

        void popAndResetState();

        std::shared_ptr<IGameState> getState() const;

    private:
        void graphicsUpdate(double t, float dt) override;

        void graphicsUpdateState() const;

        void physicsUpdate(double t, float dt) override;

        void loadResources();

        Config _config;
        std::shared_ptr<engine::Vector2f> _mouse_position;

        std::stack<std::shared_ptr<IGameState>> _states;
    };

} // game

#endif //GAME_ENGINE_GAME_H
