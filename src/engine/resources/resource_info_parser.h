#ifndef GAME_ENGINE_RESOURCE_PARSER_H
#define GAME_ENGINE_RESOURCE_PARSER_H


#include "engine/resources/TextureResource.h"
#include "engine/resources/AnimationResource.h"
#include "engine/resources/AudioResource.h"

namespace engine {

    TextureResource parse_texture_info(const std::string &filepath);

    AnimationResourceGroup parse_animation_info(const std::string &filepath);

    AudioResource parse_audio_info(const std::string &filepath);

} // engine

#endif //GAME_ENGINE_RESOURCE_PARSER_H
