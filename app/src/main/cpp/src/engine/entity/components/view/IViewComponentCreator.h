#ifndef GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_IVIEWCOMPONENTCREATOR_H


#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/entity/components/view/sprite/IAnimatedSpriteComponent.h"
#include "engine/entity/components/view/text/ITextBoxComponent.h"
#include "engine/entity/components/view/shape/ILineComponent.h"

namespace engine {

    class IViewComponentCreator {
    public:
        virtual std::shared_ptr<engine::ILineComponent> createLine(
                unsigned int layer, bool project_ui_space, const Vector2f &origin, const Vector2f &end) = 0;

        virtual std::shared_ptr<engine::IShapeComponent> createRectangle(
                const engine::Vector2f &size, unsigned int layer, bool project_ui_space) = 0;

        virtual std::shared_ptr<ISpriteComponent> createSprite(
                const engine::Vector2f &size, unsigned int layer, bool project_ui_space,
                const std::string &texture_id) = 0;

        virtual std::shared_ptr<IAnimatedSpriteComponent> createAnimatedSprite(
                const engine::Vector2f &size, unsigned int layer, bool project_ui_space,
                const std::string &animation_group_id) = 0;

        virtual std::shared_ptr<ITextBoxComponent> createTextBox(
                const engine::Vector2f &size, unsigned int layer, bool project_ui_space,
                const std::string &font) = 0;

        void setCamera(std::weak_ptr<Camera> camera);

    protected:
        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENTCREATOR_H
