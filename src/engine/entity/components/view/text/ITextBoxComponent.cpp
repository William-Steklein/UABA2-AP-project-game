#include "ITextBoxComponent.h"

namespace engine {
    ITextBoxComponent::ITextBoxComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space)
            : IShapeComponent(size, std::move(camera), project_ui_space), _font_size(0.1f), _text("") {

    }

    const std::string &ITextBoxComponent::getText() const {
        return _text;
    }

    void ITextBoxComponent::setText(const std::string &text) {
        _text = text;
        updateTextBox();
    }

    float ITextBoxComponent::getFontSize() const {
        return _font_size;
    }

    void ITextBoxComponent::setFontSize(float font_size) {
        _font_size = font_size;
        updateTextBox();
    }

    void ITextBoxComponent::updateShape() {
        updateTextBox();
    }
} // engine