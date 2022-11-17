#include "resource_info_parser.h"

namespace engine {

    inline nlohmann::json loadJsonFromFile(const std::string &filepath) {
        std::ifstream info_file = read_file(filepath);
        nlohmann::json j;
        info_file >> j;
        info_file.close();

        return j;
    }

    std::vector<TextureResource> parseTextureInfo(const std::string &filepath) {
        nlohmann::json j = loadJsonFromFile(filepath);

        std::vector<TextureResource> texture_info;

        for (const auto &item: j.items()) {
            TextureResource texture_resource;

            texture_resource.name = item.key();
            texture_resource.texture_path = item.value();

            texture_info.push_back(texture_resource);
        }

        return texture_info;
    }

    std::vector<AnimationResourceGroup> parseAnimationInfo(const std::string &filepath) {
        nlohmann::json j = loadJsonFromFile(filepath);

        std::vector<AnimationResourceGroup> animation_info;

        for (const auto &item: j.items()) {
            AnimationResourceGroup animation_resource_group;

            animation_resource_group.name = item.key();

            for (const auto &animation: item.value().items()) {
                AnimationResource animation_resource;

                animation_resource.name = animation.key();
                animation_resource.frame_time = animation.value()[0];

                for (const auto &frame: animation.value()[1]) {
                    animation_resource.frame_paths.push_back(frame);
                }

                animation_resource_group.animation_resources.push_back(animation_resource);
            }

            animation_info.push_back(animation_resource_group);
        }

        return animation_info;
    }

    std::vector<AudioResource> parseAudioInfo(const std::string &filepath) {
        nlohmann::json j = loadJsonFromFile(filepath);

        std::vector<AudioResource> audio_info;

        for (const auto &item: j.items()) {
            AudioResource audio_resource;

            audio_resource.name = item.key();
            audio_resource.audio_path = item.value();

            audio_info.push_back(audio_resource);
        }

        return audio_info;
    }

} // engine
