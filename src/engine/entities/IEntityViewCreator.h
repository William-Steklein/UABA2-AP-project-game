#ifndef GAME_ENGINE_IENTITYVIEWCREATOR_H
#define GAME_ENGINE_IENTITYVIEWCREATOR_H


#include "engine/entities/Entity.h"

namespace engine {

    class IEntityViewCreator {
    public:
        virtual std::shared_ptr<IEntityView> create(unsigned int layer, const std::string &texture_id) = 0;
    };

} // engine

#endif //GAME_ENGINE_IENTITYVIEWCREATOR_H
