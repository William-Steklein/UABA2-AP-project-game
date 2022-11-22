#ifndef GAME_ENGINE_RESOURCEMANAGER_H
#define GAME_ENGINE_RESOURCEMANAGER_H


#include <SFML/Graphics/Texture.hpp>

#include <engine/resources/IResourceManager.h>

namespace renderer {

    class ResourceManager : public engine::IResourceManager {
    public:
        void loadTextureResources(const std::vector<engine::TextureResource> &texture_resources) override;

        void loadAnimationResourceGroups(
                const std::vector<engine::AnimationResourceGroup> &animation_resource_groups) override;

        void loadAudioResources(const std::vector<engine::AudioResource> &audio_resources) override;

        std::vector<std::shared_ptr<sf::Texture>> getTextureGroup(const std::string &texture_group_id);

    private:
        std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> _texture_groups;

        bool checkTextureGroupIdLoaded(const std::string &texture_group_id) const;

        void checkTextureGroupIdExists(const std::string &texture_group_id);
    };

} // renderer


#endif //GAME_ENGINE_RESOURCEMANAGER_H
