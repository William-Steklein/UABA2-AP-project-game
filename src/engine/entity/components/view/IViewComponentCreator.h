#ifndef GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_IVIEWCOMPONENTCREATOR_H


#include "engine/entity/components/view/ISpriteComponent.h"
#include "IAnimatedSpriteComponent.h"

namespace engine {

    class IViewComponentCreator {
    public:
        virtual std::shared_ptr<ISpriteComponent> createSprite(const engine::Vector2f &size,
                                                               const std::string &texture_id,
                                                               unsigned int layer) = 0;

        virtual std::shared_ptr<IAnimatedSpriteComponent> createAnimatedSprite(const engine::Vector2f &size,
                                                                               const std::string &animation_group_id,
                                                                               unsigned int layer) = 0;

        void setCamera(std::weak_ptr<Camera> camera);

    protected:
        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
