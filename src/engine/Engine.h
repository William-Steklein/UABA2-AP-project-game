#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H

namespace engine {

    class Engine {
    public:
        Engine();

        ~Engine();

        static void sleep();

        void update();
    };

} // engine

#endif //GAME_ENGINE_ENGINE_H
