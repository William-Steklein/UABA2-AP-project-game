#ifndef GAME_ENGINE_RESOURCEMANAGER_H
#define GAME_ENGINE_RESOURCEMANAGER_H


#include <engine/resources/IResourceManager.h>

namespace renderer {

    class ResourceManager : public engine::IResourceManager {
    public:
        void loadTextureResources(const engine::TextureResource &texture_resource) override;

        void loadAnimationResourceGroups(const engine::AnimationResourceGroup &animation_resource_group) override;

        void loadAudioResources(const engine::AudioResource &audio_resource) override;

    private:

    };

} // renderer


#endif //GAME_ENGINE_RESOURCEMANAGER_H
