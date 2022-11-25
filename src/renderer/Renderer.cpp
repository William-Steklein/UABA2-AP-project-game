#include "renderer/Renderer.h"

namespace renderer {
    Renderer::Renderer() : _screen_width(constants::screen_width), _screen_height(constants::screen_height),
                           _running(true) {
        _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_screen_width, _screen_height),
                                                     constants::window_title);

        _resource_manager = std::make_shared<ResourceManager>();
        _view_component_creator = std::make_shared<ViewComponentCreator>(_resource_manager);
        _audio_component_creator = std::make_shared<AudioComponentCreator>(_resource_manager);

        _game = std::make_unique<game::Game>(0, _screen_width, _screen_height, 0,
                                             _resource_manager,
                                             _view_component_creator,
                                             _audio_component_creator);
    }

    Renderer::~Renderer() = default;

    void Renderer::run() {
        while (_running) {
            // engine sleep
            _game->sleep();

            // sfml events
            handleEvents();

            // game update
            _game->update();

            // sfml draw
            draw();
        }
    }

    void Renderer::draw() {
        _window->clear(sf::Color(127, 128, 118));

//        for (const auto &entity_view: _view_component_creator->getEntityViews()) {
//            _window->draw(*(static_cast<std::shared_ptr<sf::Drawable>>(entity_view->getSprite())));
//        }
        _view_component_creator->draw(_window);

        _window->display();
    }

    void Renderer::handleEvents() {
        sf::Event event{};
        while (_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit();
                    break;

                default:
                    break;
            }
        }
    }

    void Renderer::quit() {
        _window->close();
        _running = false;
    }
} // renderer