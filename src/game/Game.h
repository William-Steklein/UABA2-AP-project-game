#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H


#include <stack>
#include <iostream>

#include <engine/Engine.h>

#include "game/input/InputEvent.h"
#include "game/config/config_parser.h"
#include "game/level/LevelData.h"

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

        void setCurrentLevelId(unsigned int level_id);

        const std::vector<std::shared_ptr<LevelData>> &getLevelData() const;

        const std::shared_ptr<LevelData> &getLevelDataPoint(unsigned int level_id) const;

        const std::shared_ptr<LevelData> &getCurrentLevelDataPoint() const;

        bool isLastLevel() const;

        void advanceCurrentLevel();

    private:
        void graphicsUpdate(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadResources();

        Config _config;
        std::shared_ptr<engine::Vector2f> _mouse_position;

        std::stack<std::unique_ptr<IGameState>> _states;

        std::vector<std::shared_ptr<LevelData>> _level_data;
        unsigned int _current_level_id;
    };

} // game

#endif //GAME_ENGINE_GAME_H
