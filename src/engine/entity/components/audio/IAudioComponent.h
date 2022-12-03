#ifndef GAME_ENGINE_IAUDIOCOMPONENT_H
#define GAME_ENGINE_IAUDIOCOMPONENT_H


#include <map>
#include <utility>
#include <stdexcept>

#include "engine/entity/components/IComponent.h"

namespace engine {

    class IAudioComponent : public IComponent {
    public:
        IAudioComponent(std::weak_ptr<std::map<unsigned int, float>> channel_volumes);

        virtual ~IAudioComponent() = default;

        void update(double t, float dt, Transform &transform) override;

        virtual void playSound(const std::string &sound_id, unsigned int channel, bool loop) = 0;

        virtual void playMusic(const std::string &music_id, unsigned int channel, bool loop) = 0;

        virtual void setVolume(float volume) = 0;

        virtual void updateVolume() = 0;

    protected:
        float _volume;
        unsigned int _current_channel;

        float getTotalVolume();

    private:
        std::weak_ptr<std::map<unsigned int, float>> _channel_volumes;

        float getChannelVolume();
    };

} // engine

#endif //GAME_ENGINE_IAUDIOCOMPONENT_H
