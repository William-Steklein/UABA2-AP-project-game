#include "engine/Engine.h"

namespace engine {
    Engine::Engine(float screen_x_min, float screen_x_max, float screen_y_min, float screen_y_max,
                   std::shared_ptr<IResourceManager> resource_manager,
                   std::shared_ptr<IViewComponentCreator> view_component_creator)
            : _resource_manager(std::move(resource_manager)),
              _view_component_creator(std::move(view_component_creator)),
              _animation_component_creator(
                      std::make_shared<AnimationComponentCreator>(_resource_manager, _view_component_creator)),
              _camera(std::make_shared<Camera>(screen_x_min, screen_x_max, screen_y_min, screen_y_max)),
              _physics_delta_time(1.f / 60.f), _physics_time(0.f),
              _accumulator(0.f), _physics_speed(1.f) {
        _view_component_creator->setCamera(_camera);
    }

    Engine::~Engine() = default;

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

    void Engine::update(double t, float dt) {
        for (const auto &entity: _entities) {
            entity->update(t, dt);
        }
    }

    void Engine::physicsUpdate(double t, float dt) {
        for (const auto &physics_entity: _physics_entities) {
            physics_entity->update(t, dt);
        }
    }
} // engine