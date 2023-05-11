#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H


#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include <game/Game.h>
#include <game/state/IGameState.h>

#include "renderer/constants/constants.h"
#include "renderer/utils/utils.h"
#include "renderer/resources/ResourceManager.h"
#include "renderer/components/view/ViewComponentCreator.h"
#include "renderer/components/audio/AudioComponentCreator.h"
#include "renderer/input/InputChecker.h"

namespace renderer {

    /**
     * Manages the rendering of a game using the SFML library.
     */
    class Renderer {
    public:
        /**
         * Default constructor
         */
        Renderer();

        /**
         * The main game loop. This function handles events, updates the game state, and draws the game.
         */
        void run();

    private:
        unsigned int _screen_width;
        unsigned int _screen_height;
        bool _running;

        std::shared_ptr<sf::RenderWindow> _window;

        std::unique_ptr<InputChecker> _input_mapper;

        std::shared_ptr<ResourceManager> _resource_manager;
        std::shared_ptr<ViewComponentCreator> _view_component_creator;
        std::shared_ptr<AudioComponentCreator> _audio_component_creator;

        std::unique_ptr<game::Game> _game;

        /**
         * Clears the window and draws the view components.
         */
        void draw();

        /**
         * Handles SFML events and passes user input to the game.
         */
        void handleEvents();

        /**
         * Closes the window and quits the main game loop.
         */
        void quit();

        /**
         * Handles a SFML window resize event and passes the data to the game.
         * @param screen_width
         * @param screen_height
         */
        void resizeWindow(unsigned int screen_width, unsigned int screen_height);
    };

} // renderer


#endif //GAME_ENGINE_RENDERER_H
