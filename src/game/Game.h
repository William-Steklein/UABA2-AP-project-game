#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <engine/Engine.h>

#include "game/input/InputEvent.h"
#include "game/config/config_parser.h"
#include "game/state/IGameState.h"

namespace game {

    class Game : public engine::Engine {
    public:
        Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
             std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
             std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator,
             std::shared_ptr<IGameState> start_state);

        ~Game() override = default;

        void update() override;

        void handleInputs(const std::vector<engine::Input> &inputs) override;

        const std::shared_ptr<engine::Vector2f> &getMousePosition() const;

    private:
        void update(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadResources();

        Config _config;
        std::shared_ptr<IGameState> _state;
        std::shared_ptr<engine::Vector2f> _mouse_position;
    };

} // game

#endif //GAME_ENGINE_GAME_H
