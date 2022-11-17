#include "engine/Engine.h"

namespace engine {

    Engine::Engine(std::shared_ptr<IResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)), _physics_delta_time(1.f / 60.f), _physics_time(0.f),
              _accumulator(0.f), _physics_speed(1.f) {

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
            entity->update();
        }
    }

    void Engine::physicsUpdate(double t, float dt) {
        for (const auto &physics_entity: _physics_entities) {
            physics_entity->update();
        }
    }

} // engine