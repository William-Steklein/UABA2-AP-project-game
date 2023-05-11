#ifndef GAME_ENGINE_CONFIG_PARSER_H
#define GAME_ENGINE_CONFIG_PARSER_H


#include <string>

#include "engine/input/Input.h"

#include "Config.h"

namespace game {

    Config parseConfig(const std::string &filepath);

} // game

#endif //GAME_ENGINE_CONFIG_PARSER_H
