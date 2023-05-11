#include "IAudioComponentCreator.h"

namespace engine {
    IAudioComponentCreator::IAudioComponentCreator()
            : _channel_volume(std::make_shared<std::map<unsigned int, float>>()) {

    }

    void IAudioComponentCreator::setChannelVolume(unsigned int channel, float volume) {
        (*_channel_volume)[channel] = volume;

        for (auto &audio_component: _audio_components) {
            audio_component->updateVolume();
        }
    }
} // engine