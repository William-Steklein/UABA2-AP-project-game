#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H


#include "engine/Stopwatch.h"
#include "engine/logging/logging.h"

namespace engine {

    class Engine {
    public:
        Engine();

        ~Engine();

        static void sleep();

        void update();

    private:
        float _physics_delta_time;
        double _physics_time;
        float _accumulator;
        float _physics_speed;

        void update(double t, float dt);

        void physicsUpdate(double t, float dt);
    };

} // engine

#endif //GAME_ENGINE_ENGINE_H
