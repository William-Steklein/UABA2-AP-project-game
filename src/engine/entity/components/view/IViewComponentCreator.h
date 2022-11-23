#ifndef GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_IVIEWCOMPONENTCREATOR_H


#include "engine/entity/Entity.h"

namespace engine {

    class IViewComponentCreator {
    public:
        virtual std::shared_ptr<IViewComponent> create(const std::string &texture_id, unsigned int layer) = 0;

        void setCamera(std::weak_ptr<Camera> camera);

    protected:
        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
