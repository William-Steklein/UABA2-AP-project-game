#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H


#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include <game/Game.h>
#include <game/state/MenuState.h>

#include "renderer/constants/constants.h"
#include "renderer/utils.h"
#include "renderer/resources/ResourceManager.h"
#include "renderer/components/view/ViewComponentCreator.h"
#include "renderer/components/audio/AudioComponentCreator.h"
#include "renderer/InputMapper.h"

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

        std::shared_ptr<sf::RenderWindow> _window;

        std::unique_ptr<InputMapper> _input_mapper;

        std::shared_ptr<ResourceManager> _resource_manager;
        std::shared_ptr<ViewComponentCreator> _view_component_creator;
        std::shared_ptr<AudioComponentCreator> _audio_component_creator;

        std::unique_ptr<game::Game> _game;

        void draw();

        void handleEvents();

        void quit();

        void resizeWindow(unsigned int screen_width, unsigned int screen_height);
    };

} // renderer


#endif //GAME_ENGINE_RENDERER_H
