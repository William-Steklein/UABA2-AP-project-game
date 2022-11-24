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
        AudioComponent(std::shared_ptr<std::map<std::string, sf::SoundBuffer>> sounds,
                       std::shared_ptr<std::map<std::string, std::string>> music);

        ~AudioComponent() override = default;

        void playSound(const std::string &sound_id, unsigned int channel, bool loop) override;

        void playMusic(const std::string &music_id, unsigned int channel, bool loop) override;

    private:
        sf::Sound _sound_stream;
        sf::Music _music_stream;

        std::shared_ptr<std::map<std::string, sf::SoundBuffer>> _sounds;
        std::shared_ptr<std::map<std::string, std::string>> _music;
    };

} // renderer

#endif //GAME_ENGINE_AUDIOCOMPONENT_H
