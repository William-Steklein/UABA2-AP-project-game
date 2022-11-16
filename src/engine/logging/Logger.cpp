#include "Logger.h"

namespace engine {
    Logger &Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    Logger::Logger() : _debug_stream(&std::cout), _info_stream(&std::cout), _error_stream(&std::cerr) {

    }

    std::ostream *Logger::getDebugStream() const {
        return _debug_stream;
    }

    void Logger::setDebugStream(std::ostream *debugStream) {
        _debug_stream = debugStream;
    }

    std::ostream *Logger::getInfoStream() const {
        return _info_stream;
    }

    void Logger::setInfoStream(std::ostream *infoStream) {
        _info_stream = infoStream;
    }

    std::ostream *Logger::getErrorStream() const {
        return _error_stream;
    }

    void Logger::setErrorStream(std::ostream *errorStream) {
        _error_stream = errorStream;
    }
} // engine
