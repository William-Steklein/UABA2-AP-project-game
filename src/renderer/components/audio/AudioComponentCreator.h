#ifndef GAME_ENGINE_AUDIOCOMPONENTCREATOR_H
#define GAME_ENGINE_AUDIOCOMPONENTCREATOR_H


#include <utility>

#include <engine/entity/components/audio/IAudioComponentCreator.h>

#include "renderer/resources/ResourceManager.h"
#include "renderer/components/audio/AudioComponent.h"

namespace renderer {

    class AudioComponentCreator : public engine::IAudioComponentCreator {
    public:
        AudioComponentCreator(std::shared_ptr<ResourceManager> resource_manager);

        ~AudioComponentCreator() = default;

        std::shared_ptr<engine::IAudioComponent> create() override;

    private:
        std::shared_ptr<ResourceManager> _resource_manager;
    };

} // renderer

#endif //GAME_ENGINE_AUDIOCOMPONENTCREATOR_H
