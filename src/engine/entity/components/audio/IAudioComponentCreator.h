#ifndef GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H
#define GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H


#include "engine/entity/components/audio/IAudioComponent.h"

namespace engine {

    class IAudioComponentCreator {
    public:
        virtual std::shared_ptr<IAudioComponent> create() = 0;
    };

} // engine

#endif //GAME_ENGINE_IAUDIOCOMPONENTCREATOR_H
