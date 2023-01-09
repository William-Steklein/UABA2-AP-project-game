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

    /**
     * Subclass implementation of Engine interface.
     * Holds a stack of game states that implement the logic and hold the data of the game.
     *
     * Assets used:
     * - character: "https://rvros.itch.io/animated-pixel-hero"
     * - terrain and background: "https://oisougabo.itch.io/free-platformer-16x16"
     * - finish object: "https://opengameart.org/content/spinning-glassy-shapes"
     */
    class Game : public engine::Engine {
    public:
        /**
         * Constructor for Game.
         *
         * Loads config and level data.
         * @param screen_x_min
         * @param screen_x_max
         * @param screen_y_min
         * @param screen_y_max
         * @param resource_manager
         * @param view_component_creator
         * @param audio_component_creator
         */
        Game(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
             std::shared_ptr<engine::IResourceManager> resource_manager,
             std::shared_ptr<engine::IViewComponentCreator> view_component_creator,
             std::shared_ptr<engine::IAudioComponentCreator> audio_component_creator);

        /**
         * Handles engine input and convert them to game input events, which are then handled by the current game state.
         * @param inputs
         */
        void handleInputs(const std::vector<engine::Input> &inputs) override;

        const std::shared_ptr<engine::Vector2f> &getMousePosition() const;

        /**
         * Sets the level id for the level data that will be loaded when the game enters the level state.
         * @param level_id
         */
        void setCurrentLevelId(unsigned int level_id);

        /**
         * Getter for all level data
         * @return level data vector
         */
        const std::vector<std::shared_ptr<LevelData>> &getLevelData() const;

        /**
         * Getter for the level data of the current selected level.
         * @return
         */
        const std::shared_ptr<LevelData> &getCurrentLevelDataPoint() const;

        /**
         * Checks if the selected level is the last level.
         * @return last level bool
         */
        bool isLastLevel() const;

        /**
         * Advances the current selected level to the next level. Loops back around to 0.
         */
        void advanceCurrentLevel();

        /**
         * Check if framerate should be shown.
         * @return show_framerate flag
         */
        bool showFramerate() const;

    private:
        /**
         * Current state graphics update.
         * @param t
         * @param dt
         */
        void graphicsUpdate(double t, float dt) override;

        /**
         * Current state physics update.
         * @param t
         * @param dt
         */
        void physicsUpdate(double t, float dt) override;

        Config _config;

        std::shared_ptr<engine::Vector2f> _mouse_position;

        std::stack<std::unique_ptr<IGameState>> _states;

        std::vector<std::shared_ptr<LevelData>> _level_data;
        unsigned int _current_level_id;
    };

} // game

#endif //GAME_ENGINE_GAME_H
