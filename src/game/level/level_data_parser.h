#ifndef GAME_ENGINE_LEVEL_DATA_PARSER_H
#define GAME_ENGINE_LEVEL_DATA_PARSER_H


#include <string>
#include <vector>
#include <memory>

#include "game/level/LevelData.h"

namespace game {

    std::vector<std::shared_ptr<LevelData>> levelsDataParser(const std::string &filepath);

} // game

#endif //GAME_ENGINE_LEVEL_DATA_PARSER_H
