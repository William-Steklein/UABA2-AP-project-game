#include "engine/utils/windows_timersleep.h"

#ifdef WIN32

namespace engine {
    void timerSleep(double seconds) {
        using namespace std::chrono;

        static HANDLE timer = CreateWaitableTimer(nullptr, FALSE, nullptr);
        static double estimate = 5e-3;
        static double mean = 5e-3;
        static double m2 = 0;
        static int64_t count = 1;

        while (seconds - estimate > 1e-7) {
            double toWait = seconds - estimate;
            LARGE_INTEGER due;
            due.QuadPart = -int64_t(toWait * 1e7);
            auto start = high_resolution_clock::now();
            SetWaitableTimerEx(timer, &due, 0, nullptr, nullptr, nullptr, 0);
            WaitForSingleObject(timer, INFINITE);
            auto end = high_resolution_clock::now();

            double observed = static_cast<double>((end - start).count()) / 1e9;
            seconds -= observed;

            ++count;
            double error = observed - toWait;
            double delta = error - mean;
            mean += delta / static_cast<double>(count);
            m2 += delta * (error - mean);
            double stddev = sqrt(m2 / static_cast<double>((count - 1)));
            estimate = mean + stddev;
        }

        // spin lock
        auto start = high_resolution_clock::now();
        while (static_cast<double>((high_resolution_clock::now() - start).count()) / 1e9 < seconds);
    }
} // engine

#endif