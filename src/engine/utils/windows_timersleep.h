#ifndef GAME_ENGINE_WINDOWS_TIMERSLEEP_H
#define GAME_ENGINE_WINDOWS_TIMERSLEEP_H


#ifdef WIN32

#include <windows.h>
#include <cmath>
#include <chrono>

namespace engine {

    // todo: documentation
    void timerSleep(double seconds);

} // engine

#endif


#endif //GAME_ENGINE_WINDOWS_TIMERSLEEP_H
