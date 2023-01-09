#include "engine/Engine.h"

namespace engine {
    void Engine::quit() {
        _quit = true;
    }

    bool Engine::isQuit() const {
        return _quit;
    }

    void Engine::sleep() {
        Stopwatch::getInstance().sleepFrame();
    }

    void Engine::update() {
        // physics update
        _accumulator += Stopwatch::getInstance().getDeltaTime() * _physics_speed;
        while (_accumulator >= _physics_delta_time) {
            physicsUpdate(_physics_time, _physics_delta_time);

            _accumulator -= _physics_delta_time;
            _physics_time += _physics_delta_time;
        }

        // graphics update
        graphicsUpdate(Stopwatch::getInstance().getTime(), Stopwatch::getInstance().getDeltaTime());
    }

    void Engine::updateScreenResolution(float screen_x_min, float screen_x_max,
                                        float screen_y_min, float screen_y_max) {
        _camera->setScreenBoundaries(screen_x_min, screen_x_max, screen_y_min, screen_y_max);
        std::tuple<Vector2f, Vector2f, Vector2f> sidebar_data = _camera->getSidebarData();
        _sidebar1->setPosition(std::get<1>(sidebar_data));
        _sidebar2->setPosition(std::get<2>(sidebar_data));
        _sidebar1->setScale(std::get<0>(sidebar_data));
        _sidebar2->setScale(std::get<0>(sidebar_data));
    }

    const std::shared_ptr<IResourceManager> &Engine::getResourceManager() const {
        return _resource_manager;
    }

    const std::shared_ptr<IViewComponentCreator> &Engine::getViewComponentCreator() const {
        return _view_component_creator;
    }

    const std::shared_ptr<IAudioComponentCreator> &Engine::getAudioComponentCreator() const {
        return _audio_component_creator;
    }

    const std::shared_ptr<Camera> &Engine::getCamera() const {
        return _camera;
    }

    Engine::Engine(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
                   std::shared_ptr<IResourceManager> resource_manager,
                   std::shared_ptr<IViewComponentCreator> view_component_creator,
                   std::shared_ptr<IAudioComponentCreator> audio_component_creator)
            : _resource_manager(std::move(resource_manager)),
              _view_component_creator(std::move(view_component_creator)),
              _audio_component_creator(std::move(audio_component_creator)),
              _camera(std::make_shared<Camera>(screen_x_min, screen_x_max, screen_y_min, screen_y_max)),
              _quit(false),
              _physics_delta_time(1.f / constants::physics_framerate_limit), _physics_time(0.f),
              _accumulator(0.f), _physics_speed(1.f) {
        _view_component_creator->setCamera(_camera);

        try {
            _resource_manager->loadResources("data/resource-info/resources.json");
        } catch (const std::exception &e) {
            LOGERROR(e.what());
            LOGERROR("Unable to load resource data");

            quit();
        }
    }

    void Engine::initSidebars(unsigned int layer) {
        std::tuple<Vector2f, Vector2f, Vector2f> sidebar_data = _camera->getSidebarData();

        _sidebar1 = std::make_shared<Entity>(Entity(
                {std::get<1>(sidebar_data), std::get<0>(sidebar_data), 0},
                {_view_component_creator->createRectangle({1, 1}, layer, true)}
        ));
        _sidebar2 = std::make_shared<Entity>(Entity(
                {std::get<2>(sidebar_data), std::get<0>(sidebar_data), 0},
                {_view_component_creator->createRectangle({1, 1}, layer, true)}
        ));
    }

    void Engine::graphicsUpdate(double t, float dt) {
        _sidebar1->graphicsUpdate(t, dt);
        _sidebar2->graphicsUpdate(t, dt);
    }

    void Engine::physicsUpdate(double t, float dt) {

    }
} // engine