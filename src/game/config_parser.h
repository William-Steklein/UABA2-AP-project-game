#ifndef GAME_ENGINE_CONFIG_PARSER_H
#define GAME_ENGINE_CONFIG_PARSER_H


#include <string>

#include <engine/utils/file_io.h>
#include <engine/Input.h>

#include "game/Config.h"

namespace game {

    Config parseConfig(const std::string &filepath);

} // game

#endif //GAME_ENGINE_CONFIG_PARSER_H
