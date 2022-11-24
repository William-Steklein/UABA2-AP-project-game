#include "IAudioComponent.h"

namespace engine {
    IAudioComponent::IAudioComponent(std::weak_ptr<std::map<unsigned int, float>> channel_volumes)
            : _volume(100), _current_channel(0), _channel_volumes(std::move(channel_volumes)) {

    }

    void IAudioComponent::update(double t, float dt, Entity &entity) {

    }

    float IAudioComponent::getTotalVolume() {
        return _volume * (getChannelVolume() / 100.f);
    }

    float IAudioComponent::getChannelVolume() {
        if (_channel_volumes.expired()) {
            throw std::runtime_error("An audio component has no channel volumes");
        }

        std::shared_ptr<std::map<unsigned int, float>> shared_channel_volumes = _channel_volumes.lock();

        // check if channel already has a volume, assign one otherwise
        if (shared_channel_volumes->find(_current_channel) == shared_channel_volumes->end()) {
            (*shared_channel_volumes)[_current_channel] = 100;
            return 100;
        }

        return shared_channel_volumes->at(_current_channel);
    }
} // engine