#ifndef GAME_ENGINE_STOPWATCH_H
#define GAME_ENGINE_STOPWATCH_H


#include <chrono>
#include <thread>
#include <iostream>

#include "engine/constants/constants.h"
#include "engine/utils/windows_timersleep.h"
#include "engine/logging/Logger.h"

namespace engine {

    class Stopwatch {
    public:
        Stopwatch(const Stopwatch &) = delete;

        Stopwatch &operator=(const Stopwatch &) = delete;

        static Stopwatch &getInstance();

        void sleepFrame();

        float getDeltaTime() const;

        double getTime() const;

        bool isCapFramerate() const;

        void setCapFramerate(bool cap_framerate);

        float getFramerateLimit() const;

        void setFramerateLimit(float frame_duration_limit);

        float getAverageFps() const;

        float getAverageMs() const;

    private:
        Stopwatch();

        std::chrono::steady_clock::time_point _a;
        std::chrono::steady_clock::time_point _b;
        float _frame_duration_limit;
        bool _cap_framerate;
        float _delta_time;
        double _time;

        float _sample_duration;
        float _duration;
        float _frame_count;
        float _average_framerate;
    };

} // engine

#endif //GAME_ENGINE_STOPWATCH_H
