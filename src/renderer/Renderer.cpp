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
        _window->clear(colorEngineToSFML(constants::window_clear_color));

        _view_component_creator->draw(_window);

        _window->display();
    }

    void Renderer::handleEvents() {
        if (_game->isQuit()) quit();

        std::vector<engine::Input> inputs;

        sf::Event event{};
        while (_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit();
                    break;

                case sf::Event::Resized:
                    resizeWindow(_window->getSize().x, _window->getSize().y);
                    break;

                default:
                    // input mapping
                    engine::Input input = mapInput(event, _window);

                    if (input.type != engine::Input::InputType::UNDEFINEDTYPE) {
                        inputs.push_back(input);
                    }
            }
        }

        _game->handleInputs(inputs);
    }

    void Renderer::quit() {
        _window->close();
        _running = false;
    }

    void Renderer::resizeWindow(unsigned int screen_width, unsigned int screen_height) {
        _screen_width = screen_width;
        _screen_height = screen_height;

        // update the view to the new screen_ui_size of the window
        sf::FloatRect visibleArea(0, 0, static_cast<float>(screen_width), static_cast<float>(screen_height));
        _window->setView(sf::View(visibleArea));

        _game->updateScreenResolution(0, static_cast<float>(screen_width), static_cast<float>(screen_height), 0);
    }
} // renderer