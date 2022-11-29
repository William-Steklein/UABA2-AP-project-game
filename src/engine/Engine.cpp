#include "engine/Engine.h"

namespace engine {
    Engine::Engine(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
                   std::shared_ptr<IResourceManager> resource_manager,
                   std::shared_ptr<IViewComponentCreator> view_component_creator,
                   std::shared_ptr<IAudioComponentCreator> audio_component_creator)
            : _resource_manager(std::move(resource_manager)),
              _view_component_creator(std::move(view_component_creator)),
              _audio_component_creator(std::move(audio_component_creator)),
              _camera(std::make_shared<Camera>(screen_x_min, screen_x_max, screen_y_min, screen_y_max)),
              _physics_delta_time(1.f / 60.f), _physics_time(0.f),
              _accumulator(0.f), _physics_speed(1.f) {
        _view_component_creator->setCamera(_camera);
        initSidebars();
    }

    void Engine::sleep() {
        Stopwatch::getInstance().sleepFrame();
    }

    void Engine::update() {
        // engine update
        update(Stopwatch::getInstance().getTime(), Stopwatch::getInstance().getDeltaTime());

        // physics update
        _accumulator += Stopwatch::getInstance().getDeltaTime() * _physics_speed;
        while (_accumulator >= _physics_delta_time) {
            physicsUpdate(_physics_time, _physics_delta_time);

            _accumulator -= _physics_delta_time;
            _physics_time += _physics_delta_time;
        }
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

    void Engine::initSidebars() {
        std::tuple<Vector2f, Vector2f, Vector2f> sidebar_data = _camera->getSidebarData();

        _sidebar1 = std::make_shared<Entity>(Entity(
                {std::get<1>(sidebar_data), std::get<0>(sidebar_data), 0},
                {_view_component_creator->createRectangle({1, 1}, 10)}
        ));
        _sidebar2 = std::make_shared<Entity>(Entity(
                {std::get<2>(sidebar_data), std::get<0>(sidebar_data), 0},
                {_view_component_creator->createRectangle({1, 1}, 10)}
        ));
    }

    void Engine::update(double t, float dt) {
        _sidebar1->update(t, dt);
        _sidebar2->update(t, dt);
    }

    void Engine::physicsUpdate(double t, float dt) {

    }
} // engine