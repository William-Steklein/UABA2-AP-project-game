#ifndef GAME_ENGINE_FILE_IO_H
#define GAME_ENGINE_FILE_IO_H


#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include "engine/logging/Logger.h"

namespace engine {

    std::ifstream read_file(const std::string &filepath);

    std::ofstream write_file(const std::string &filepath);

    nlohmann::json loadJsonFromFile(const std::string &filepath);

} // engine

#endif //GAME_ENGINE_FILE_IO_H
