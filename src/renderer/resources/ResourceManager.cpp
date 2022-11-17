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
            if (checkTextureNameExists(texture_resource.name)) continue;

            std::shared_ptr<sf::Texture> texture = loadTextureFromFile(texture_resource.texture_path);

            _texture_groups[texture_resource.name] = {texture};
        }
    }

    void ResourceManager::loadAnimationResourceGroups(
            const std::vector<engine::AnimationResourceGroup> &animation_resource_groups) {

    }

    void ResourceManager::loadAudioResources(const std::vector<engine::AudioResource> &audio_resources) {

    }

// check if texture id is already loaded
    bool ResourceManager::checkTextureNameExists(const std::string &texture_name) const {
        if (_texture_groups.find(texture_name) != _texture_groups.end()) {
            LOGERROR("Texture with id \"" + texture_name + "\" already exists");
            return true;
        }

        return false;
    }

} // renderer