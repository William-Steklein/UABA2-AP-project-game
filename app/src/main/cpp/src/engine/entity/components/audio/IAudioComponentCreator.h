#ifndef GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H
#define GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H


#include <map>
#include <vector>

#include "engine/entity/components/audio/IAudioComponent.h"

namespace engine {

    class IAudioComponentCreator {
    public:
        IAudioComponentCreator();

        virtual std::shared_ptr<IAudioComponent> create() = 0;

        virtual void setChannelVolume(unsigned int channel, float volume);

    protected:
        std::vector<std::shared_ptr<IAudioComponent>> _audio_components;
        std::shared_ptr<std::map<unsigned int, float>> _channel_volume;
    };

} // engine

#endif //GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H
