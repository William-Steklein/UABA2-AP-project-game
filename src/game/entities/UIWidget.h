#ifndef GAME_ENGINE_UIWIDGET_H
#define GAME_ENGINE_UIWIDGET_H


#include <engine/entity/Entity.h>
#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/entity/components/view/shape/IShapeComponent.h"
#include "engine/entity/components/view/text/ITextBoxComponent.h"

namespace game {

    class UIWidget : public engine::Entity {
    public:
        UIWidget(const engine::Transform &transform,
                 std::shared_ptr<engine::ISpriteComponent> sprite,
                 std::shared_ptr<engine::IShapeComponent> rectangle,
                 std::shared_ptr<engine::ITextBoxComponent> text);

        void update(double t, float dt) override;

    private:
        std::shared_ptr<engine::ISpriteComponent> _sprite;
        std::shared_ptr<engine::IShapeComponent> _rectangle;
        std::shared_ptr<engine::ITextBoxComponent> _textbox;
    };

} // game

#endif //GAME_ENGINE_UIWIDGET_H
