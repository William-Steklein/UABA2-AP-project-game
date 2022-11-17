#ifndef GAME_ENGINE_IRESOURCEMANAGER_H
#define GAME_ENGINE_IRESOURCEMANAGER_H


#include "engine/resources/resource_info_parser.h"

namespace engine {

    class IResourceManager {
    public:
        virtual void loadTextureResources(const std::vector<TextureResource> &texture_resource) = 0;

        virtual void
        loadAnimationResourceGroups(const std::vector<AnimationResourceGroup> &animation_resource_group) = 0;

        virtual void loadAudioResources(const std::vector<AudioResource> &audio_resource) = 0;

        // todo: font loading
    };

} // engine


#endif //GAME_ENGINE_IRESOURCEMANAGER_H
