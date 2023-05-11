#include "resource_info_parser.h"

namespace engine {
    std::vector<TextureResource> parseTextureInfo(const std::string &filepath) {
        nlohmann::json j = loadJsonFromFile(filepath);

        std::vector<TextureResource> texture_info;

        for (const auto &item: j.items()) {
            TextureResource texture_resource;

            texture_resource.id = item.key();
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

            animation_resource_group.id = item.key();

            for (const auto &animation: item.value().items()) {
                AnimationResource animation_resource;

                animation_resource.frame_time = animation.value()[0];

                for (const auto &frame: animation.value()[1]) {
                    animation_resource.frame_paths.push_back(frame);
                }

                animation_resource_group.animation_resources[animation.key()] = animation_resource;
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

            audio_resource.id = item.key();
            audio_resource.audio_path = item.value();

            audio_info.push_back(audio_resource);
        }

        return audio_info;
    }

    std::vector<FontResource> parseFontInfo(const std::string &filepath) {
        nlohmann::json j = loadJsonFromFile(filepath);

        std::vector<FontResource> font_info;

        for (const auto &item: j.items()) {
            FontResource font_resource;

            font_info.push_back({item.key(), item.value()});
        }

        return font_info;
    }
} // engine
