#ifndef GAME_ENGINE_AUDIOCOMPONENT_H
#define GAME_ENGINE_AUDIOCOMPONENT_H


#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include <engine/entity/components/audio/IAudioComponent.h>

namespace renderer {

    class AudioComponent : public engine::IAudioComponent {
    public:
        AudioComponent(std::weak_ptr<std::map<unsigned int, float>> channelVolumes,
                       std::shared_ptr<std::map<std::string, sf::SoundBuffer>> sound_buffers,
                       std::shared_ptr<std::map<std::string, std::string>> music_files);

        ~AudioComponent() override = default;

        void playSound(const std::string &sound_id, unsigned int channel, bool loop) override;

        void playMusic(const std::string &music_id, unsigned int channel, bool loop) override;

        void setVolume(float volume) override;

        void updateVolume() override;

    private:
        sf::Sound _sound;
        sf::Music _music;

        std::shared_ptr<std::map<std::string, sf::SoundBuffer>> _sound_buffers;
        std::shared_ptr<std::map<std::string, std::string>> _music_files;
    };

} // renderer

#endif //GAME_ENGINE_AUDIOCOMPONENT_H
