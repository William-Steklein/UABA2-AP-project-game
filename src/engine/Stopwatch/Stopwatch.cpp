#include "Stopwatch.h"

namespace engine {
    Stopwatch::Stopwatch()
            : _a(std::chrono::steady_clock::now()), _b(std::chrono::steady_clock::now()),
              _frame_duration_limit(1.f / constants::framerate_limit), _cap_framerate(constants::cap_framerate),
              _delta_time(0.f), _time(0.f),
              _sample_duration(constants::sample_duration), _duration(0.f), _frame_count(0.f),
              _average_framerate(-1.f) {

    }

    Stopwatch &Stopwatch::getInstance() {
        static Stopwatch instance;
        return instance;
    }

    void Stopwatch::sleepFrame() {
        _a = std::chrono::steady_clock::now();
        std::chrono::duration<float> work_time = _a - _b;

        if (_cap_framerate & (work_time.count() < _frame_duration_limit)) {
            std::chrono::duration<float> sleep_time(_frame_duration_limit - work_time.count());

#ifdef WIN32
            timerSleep(sleep_time.count());
#else
            std::this_thread::sleep_for(
                    std::chrono::nanoseconds(std::chrono::duration_cast<std::chrono::nanoseconds>(sleep_time)));
#endif
        }

        _b = std::chrono::steady_clock::now();
        std::chrono::duration<float> time_slept = _b - _a;
        _delta_time = (work_time + time_slept).count();

        // average framerate counter
        _frame_count++;
        _duration += _delta_time;

        if (_duration >= _sample_duration) {
            _average_framerate = _frame_count / _duration;

            _frame_count = 0.f;
            _duration = 0.f;
        } else if (_average_framerate == -1.f) {
            _average_framerate = 1 / _delta_time;
        }
    }

    float Stopwatch::getDeltaTime() const {
        return _delta_time;
    }

    double Stopwatch::getTime() const {
        return _time;
    }

    bool Stopwatch::isCapFramerate() const {
        return _cap_framerate;
    }

    void Stopwatch::setCapFramerate(bool cap_framerate) {
        _cap_framerate = cap_framerate;
    }

    float Stopwatch::getFramerateLimit() const {
        return _frame_duration_limit;
    }

    void Stopwatch::setFramerateLimit(float frame_duration_limit) {
        _frame_duration_limit = frame_duration_limit;
    }

    float Stopwatch::getAverageFps() const {
        return _average_framerate;
    }

    float Stopwatch::getAverageMs() const {
        return 1 / _average_framerate;
    }
} // engine