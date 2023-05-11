#ifndef GAME_ENGINE_FILE_IO_H
#define GAME_ENGINE_FILE_IO_H


#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include "engine/logging/Logger.h"
#include "engine/utils/FileReadSingleton.h"

namespace engine {

    std::string readFile(const std::string &filepath);

    nlohmann::json loadJsonFromFile(const std::string &filepath);

} // engine

#endif //GAME_ENGINE_FILE_IO_H
