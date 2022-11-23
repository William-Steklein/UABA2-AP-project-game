#include "ResourceManager.h"

namespace renderer {
    inline std::shared_ptr<sf::Texture> loadTextureFromFile(const std::string &filepath) {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(filepath)) {
            throw std::runtime_error("Unable load texture from file \"" + filepath + "\"");
        }

        return texture;
    }

    void ResourceManager::loadTextureResources(const std::vector<engine::TextureResource> &texture_resources) {
        for (const auto &texture_resource: texture_resources) {
            if (checkTextureGroupIdLoaded(texture_resource.id)) continue;

            std::shared_ptr<sf::Texture> texture = loadTextureFromFile(texture_resource.texture_path);

            _texture_groups[texture_resource.id] = {texture};
        }
    }

    void ResourceManager::loadAnimationResourceGroups(
            const std::vector<engine::AnimationResourceGroup> &animation_resource_groups) {
        for (const auto &animation_resource_group: animation_resource_groups) {
            if (checkTextureGroupIdLoaded(animation_resource_group.id)) continue;

            for (const auto &animation_resource: animation_resource_group.animation_resources) {
                for (const auto &frame_path: animation_resource.second.frame_paths) {
                    std::shared_ptr<sf::Texture> texture = loadTextureFromFile(frame_path);

                    if (_texture_groups.find(animation_resource_group.id) == _texture_groups.end()) {
                        _texture_groups[animation_resource_group.id] = {texture};
                    } else {
                        _texture_groups[animation_resource_group.id].push_back(texture);
                    }
                }
            }
        }

        engine::IResourceManager::loadAnimationResourceGroups(animation_resource_groups);
    }

    void ResourceManager::loadAudioResources(const std::vector<engine::AudioResource> &audio_resources) {

    }

    std::vector<std::shared_ptr<sf::Texture>> ResourceManager::getTextureGroup(const std::string &texture_group_id) {
        checkTextureGroupIdExists(texture_group_id);

        return _texture_groups.at(texture_group_id);
    }

    /* check if texture id is already loaded */
    bool ResourceManager::checkTextureGroupIdLoaded(const std::string &texture_group_id) const {
        if (_texture_groups.find(texture_group_id) != _texture_groups.end()) {
            LOGERROR("Texture with id \"" + texture_group_id + "\" already exists");
            return true;
        }

        return false;
    }

    void ResourceManager::checkTextureGroupIdExists(const std::string &texture_group_id) {
        if (_texture_groups.find(texture_group_id) == _texture_groups.end()) {
            throw std::runtime_error("Unable to get texture group with id \"" + texture_group_id + "\"");
        }
    }
} // renderer