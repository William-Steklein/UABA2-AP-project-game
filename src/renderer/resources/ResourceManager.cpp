#include "ResourceManager.h"

namespace renderer {
    inline std::shared_ptr<sf::Texture> loadTextureFromFile(const std::string &filepath) {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(filepath)) {
            throw std::runtime_error("Unable load texture from file \"" + filepath + "\"");
        }

        return texture;
    }

    ResourceManager::ResourceManager()
            : _sounds(std::make_shared<std::map<std::string, sf::SoundBuffer>>()),
              _music(std::make_shared<std::map<std::string, std::string>>()) {

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

    void ResourceManager::loadSoundResources(const std::vector<engine::AudioResource> &sound_resources) {
        for (const auto &sound_resource: sound_resources) {
            sf::SoundBuffer sound_buffer;

            if (!sound_buffer.loadFromFile(sound_resource.audio_path)) {
                throw std::runtime_error("Unable to load sound from file \"" + sound_resource.audio_path + "\"");
            }

            if (_sounds->find(sound_resource.id) == _sounds->end()) {
                (*_sounds)[sound_resource.id] = sound_buffer;
            } else {
                throw std::runtime_error("Sound with id \"" + sound_resource.id + "\" already exists");
            }
        }
    }

    void ResourceManager::loadMusicResources(const std::vector<engine::AudioResource> &music_resources) {
        for (const auto &music_resource: music_resources) {
            if (_music->find(music_resource.id) == _music->end()) {
                (*_music)[music_resource.id] = music_resource.audio_path;
            } else {
                throw std::runtime_error("Music with id \"" + music_resource.id + "\" already exists");
            }
        }
    }

    std::vector<std::shared_ptr<sf::Texture>> ResourceManager::getTextureGroup(const std::string &texture_group_id) {
        if (_texture_groups.find(texture_group_id) == _texture_groups.end()) {
            throw std::runtime_error("Unable to get texture group with id \"" + texture_group_id + "\"");
        }

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

    std::shared_ptr<std::map<std::string, sf::SoundBuffer>> ResourceManager::getSounds() {
        return _sounds;
    }

    std::shared_ptr<std::map<std::string, std::string>> ResourceManager::getMusic() {
        return _music;
    }
} // renderer