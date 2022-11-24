#ifndef GAME_ENGINE_IAUDIOCOMPONENT_H
#define GAME_ENGINE_IAUDIOCOMPONENT_H


#include "engine/entity/components/IComponent.h"

namespace engine {

    class IAudioComponent : public IComponent {
    public:
        IAudioComponent();

        virtual ~IAudioComponent() = default;

        void update(double t, float dt, Entity &entity) override;

        virtual void playSound(const std::string &sound_id, unsigned int channel, bool loop) = 0;

        virtual void playMusic(const std::string &music_id, unsigned int channel, bool loop) = 0;

    private:

    };

} // engine

#endif //GAME_ENGINE_IAUDIOCOMPONENT_H
