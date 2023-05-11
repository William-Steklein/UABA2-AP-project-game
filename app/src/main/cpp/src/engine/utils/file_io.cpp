#include "file_io.h"

namespace engine {
    std::string readFile(const std::string &filepath) {
        return FileReadSingleton::getInstance().readFile(filepath);
    }

    nlohmann::json loadJsonFromFile(const std::string &filepath) {
        return nlohmann::json::parse(readFile(filepath));
    }
} // engine