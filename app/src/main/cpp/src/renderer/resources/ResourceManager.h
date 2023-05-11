#ifndef GAME_ENGINE_RESOURCEMANAGER_H
#define GAME_ENGINE_RESOURCEMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>

#include <engine/resources/IResourceManager.h>

namespace renderer {

    class ResourceManager : public engine::IResourceManager {
    public:
        ResourceManager();

        ~ResourceManager() = default;

        void loadTextureResources(const std::vector<engine::TextureResource> &texture_resources) override;

        void loadAnimationResources(
                const std::vector<engine::AnimationResourceGroup> &animation_resource_groups) override;

        void loadSoundResources(const std::vector<engine::AudioResource> &sound_resources) override;

        void loadMusicResources(const std::vector<engine::AudioResource> &music_resources) override;

        void loadFontResources(const std::vector<engine::FontResource> &font_resources) override;

        std::vector<std::shared_ptr<sf::Texture>> getTextureGroup(const std::string &texture_group_id);

        std::shared_ptr<std::map<std::string, sf::SoundBuffer>> getSounds();

        std::shared_ptr<std::map<std::string, std::string>> getMusic();

        std::shared_ptr<sf::Font> getFont(const std::string &font_id);

    private:
        std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> _texture_groups;
        std::shared_ptr<std::map<std::string, sf::SoundBuffer>> _sounds;
        std::shared_ptr<std::map<std::string, std::string>> _music;
        std::map<std::string, std::shared_ptr<sf::Font>> _fonts;

        bool checkTextureGroupIdLoaded(const std::string &texture_group_id) const;
    };

} // renderer


#endif //GAME_ENGINE_RESOURCEMANAGER_H
