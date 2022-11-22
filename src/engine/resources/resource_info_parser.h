#ifndef GAME_ENGINE_RESOURCE_PARSER_H
#define GAME_ENGINE_RESOURCE_PARSER_H


#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "engine/utils/file_io.h"
#include "engine/resources/Resources.h"

namespace engine {

    std::vector<TextureResource> parseTextureInfo(const std::string &filepath);

    std::vector<AnimationResourceGroup> parseAnimationInfo(const std::string &filepath);

    std::vector<AudioResource> parseAudioInfo(const std::string &filepath);

} // engine

#endif //GAME_ENGINE_RESOURCE_PARSER_H
