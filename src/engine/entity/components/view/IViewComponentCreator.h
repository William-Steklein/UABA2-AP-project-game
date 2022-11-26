#ifndef GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_IVIEWCOMPONENTCREATOR_H


#include "engine/entity/components/view/ISpriteComponent.h"
#include "engine/entity/components/view/IAnimatedSpriteComponent.h"
#include "engine/entity/components/view/ITextBoxComponent.h"

namespace engine {

    class IViewComponentCreator {
    public:
        virtual std::shared_ptr<ISpriteComponent> createSprite(const engine::Vector2f &size, unsigned int layer,
                                                               const std::string &texture_id) = 0;

        virtual std::shared_ptr<IAnimatedSpriteComponent> createAnimatedSprite(
                const engine::Vector2f &size, unsigned int layer, const std::string &animation_group_id) = 0;

        virtual std::shared_ptr<ITextBoxComponent> createTextBox(
                const engine::Vector2f &size, unsigned int layer, const std::string &font,
                float font_size, const engine::Color &color, const std::string &text) = 0;

        void setCamera(std::weak_ptr<Camera> camera);

    protected:
        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
