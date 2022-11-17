#ifndef GAME_ENGINE_LOGGER_H
#define GAME_ENGINE_LOGGER_H

#include <iostream>
#include <string>

namespace engine {

    class Logger {
    public:
        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        static Logger &getInstance();

        std::ostream *getDebugStream() const;

        void setDebugStream(std::ostream *debugStream);

        std::ostream *getInfoStream() const;

        void setInfoStream(std::ostream *infoStream);

        std::ostream *getErrorStream() const;

        void setErrorStream(std::ostream *errorStream);

    private:
        Logger();

        std::ostream *_debug_stream;
        std::ostream *_info_stream;
        std::ostream *_error_stream;
    };

} // engine

#ifndef NDEBUG
#define LOGDEBUG(message) *engine::Logger::getInstance().getDebugStream() << message << std::endl
#else
#define LOGDEBUG(message)
#endif

#define LOGINFO(message) *engine::Logger::getInstance().getInfoStream() << message << std::endl

#define LOGERROR(message) *engine::Logger::getInstance().getErrorStream() << message << std::endl

#endif //GAME_ENGINE_LOGGER_H
