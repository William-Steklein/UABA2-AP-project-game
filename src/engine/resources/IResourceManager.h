#ifndef GAME_ENGINE_IRESOURCEMANAGER_H
#define GAME_ENGINE_IRESOURCEMANAGER_H


#include "engine/resources/resource_info_parser.h"
#include "engine/resources/Animation.h"
#include "engine/constants/constants.h"

namespace engine {

    class IResourceManager {
    public:
        virtual void loadTextureResources(const std::vector<TextureResource> &texture_resources) = 0;

        virtual void
        loadAnimationResourceGroups(const std::vector<AnimationResourceGroup> &animation_resource_groups);

        virtual void loadSoundResources(const std::vector<AudioResource> &audio_resources) = 0;

        virtual void loadMusicResources(const std::vector<AudioResource> &music_resources) = 0;

        // todo: font loading

        std::shared_ptr<AnimationGroup> getAnimationGroup(const std::string &animation_group_id);

    private:
        std::map<std::string, std::shared_ptr<AnimationGroup>> _animation_groups;
    };

} // engine


#endif //GAME_ENGINE_IRESOURCEMANAGER_H
