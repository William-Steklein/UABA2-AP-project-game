#include "UIWidget.h"

namespace game {
    UIWidget::UIWidget(const engine::Transform &transform, std::shared_ptr<engine::ISpriteComponent> sprite,
                       std::shared_ptr<engine::ITextBoxComponent> text)
            : engine::Entity(transform), _sprite(std::move(sprite)), _textbox(std::move(text)) {
        addComponent(_sprite);
        addComponent(_textbox);
    }

    void UIWidget::update(double t, float dt) {
//        _textbox->setFontSize(2.5f);
//        _textbox->setText("bana");

        Entity::update(t, dt);
    }
} // game