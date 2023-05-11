#include "AudioComponentCreator.h"

namespace renderer {
    AudioComponentCreator::AudioComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {}

    std::shared_ptr<engine::IAudioComponent> AudioComponentCreator::create() {
        std::shared_ptr<engine::IAudioComponent> component =
                std::make_shared<AudioComponent>(_channel_volume,
                                                 _resource_manager->getSounds(),
                                                 _resource_manager->getMusic());

        _audio_components.push_back(component);

        return component;
    }
} // renderer