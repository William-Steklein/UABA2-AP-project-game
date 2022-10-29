#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H


#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "constants.h"

namespace renderer {

    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void run();

    private:
        unsigned int _screen_width;
        unsigned int _screen_height;
        bool _running;

        std::unique_ptr<sf::RenderWindow> _window;

        std::unique_ptr<game::Game> _game;

        void draw();

        void handleEvents();

        void quit();
    };

} // renderer


#endif //GAME_ENGINE_RENDERER_H
