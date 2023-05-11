#include "AudioComponent.h"
#include "engine/logging/Logger.h"

namespace renderer {
    AudioComponent::AudioComponent(std::weak_ptr<std::map<unsigned int, float>> channelVolumes,
                                   std::shared_ptr<std::map<std::string, sf::SoundBuffer>> sound_buffers,
                                   std::shared_ptr<std::map<std::string, std::string>> music_files)
            : IAudioComponent(std::move(channelVolumes)), _sound_buffers(std::move(sound_buffers)),
              _music_files(std::move(music_files)) {

    }

    void AudioComponent::playSound(const std::string &sound_id, unsigned int channel, bool loop) {
        _sound.stop();

        if (_sound_buffers->find(sound_id) == _sound_buffers->end()) {
            throw std::runtime_error("Unable to find sound with id \"" + sound_id + "\"");
        }

        _current_channel = channel;
        _sound.setLoop(loop);
        _sound.setVolume(getTotalVolume());

        _sound.setBuffer(_sound_buffers->at(sound_id));
        _sound.play();
    }

    void AudioComponent::playMusic(const std::string &music_id, unsigned int channel, bool loop) {
        _music.stop();

        if (_music_files->find(music_id) == _music_files->end()) {
            throw std::runtime_error("Unable to find music with id \"" + music_id + "\"");
        }

        _current_channel = channel;
        _music.setLoop(loop);
        _sound.setVolume(getTotalVolume());

        if (!_music.openFromFile(_music_files->at(music_id))) {
            throw std::runtime_error("Unable to load music from file \"" + _music_files->at(music_id) + "\"");
        }
        _music.play();
    }

    void AudioComponent::setVolume(float volume) {
        _volume = volume;
        updateVolume();
    }

    void AudioComponent::updateVolume() {
        float total_volume = getTotalVolume();
        _sound.setVolume(total_volume);
        _music.setVolume(total_volume);
    }
} // renderer