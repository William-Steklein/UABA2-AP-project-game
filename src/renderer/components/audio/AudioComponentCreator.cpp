#include "AudioComponentCreator.h"

namespace renderer {
    AudioComponentCreator::AudioComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {}

    std::shared_ptr<engine::IAudioComponent> AudioComponentCreator::create() {
        return std::make_shared<AudioComponent>(_resource_manager->getSounds(), _resource_manager->getMusic());
    }
} // renderer