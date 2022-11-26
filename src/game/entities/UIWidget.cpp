#include "UIWidget.h"

namespace game {
    UIWidget::UIWidget(const engine::Transform &transform, std::shared_ptr<engine::ISpriteComponent> sprite,
                       std::shared_ptr<engine::IShapeComponent> rectangle,
                       std::shared_ptr<engine::ITextBoxComponent> text)
            : engine::Entity(transform),
            _sprite(std::move(sprite)), _rectangle(std::move(rectangle)), _textbox(std::move(text)) {
        addComponents({_sprite, _textbox, _rectangle});

        _textbox->setFontSize(0.2f);
        _textbox->setText("banana");

        _rectangle->setFillcolor({200, 200, 0, 100});
    }

    void UIWidget::update(double t, float dt) {
        Entity::update(t, dt);
    }
} // game