#include "AudioComponent.h"

namespace renderer {
    AudioComponent::AudioComponent(std::shared_ptr<std::map<std::string, sf::SoundBuffer>> sounds,
                                   std::shared_ptr<std::map<std::string, std::string>> music)
            : _sounds(std::move(sounds)), _music(std::move(music)) {

    }

    void AudioComponent::playSound(const std::string &sound_id, unsigned int channel, bool loop) {
        if (_sounds->find(sound_id) == _sounds->end()) {
            throw std::runtime_error("Unable to find sound with id \"" + sound_id + "\"");
        }

        _sound_stream.setLoop(loop);
        _sound_stream.setBuffer(_sounds->at(sound_id));
        _sound_stream.play();
    }

    void AudioComponent::playMusic(const std::string &music_id, unsigned int channel, bool loop) {
        if (_music->find(music_id) == _music->end()) {
            throw std::runtime_error("Unable to find music with id \"" + music_id + "\"");
        }

        if (!_music_stream.openFromFile(_music->at(music_id))) {
            throw std::runtime_error("Unable to load music from file \"" + _music->at(music_id) + "\"");
        }

        _music_stream.setLoop(loop);
        _music_stream.play();
    }
} // renderer