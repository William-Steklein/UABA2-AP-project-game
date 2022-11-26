#include "ITextBoxComponent.h"

namespace engine {
    ITextBoxComponent::ITextBoxComponent(const Vector2f &size, std::weak_ptr<Camera> camera,
                                         float font_size, const Color &color, const std::string &text)
            : IViewComponent(size, std::move(camera)), _font_size(font_size), _color(color), _text(text) {

    }

    void ITextBoxComponent::update(double t, float dt, Entity &entity) {

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

    const Color &ITextBoxComponent::getColor() const {
        return _color;
    }

    void ITextBoxComponent::setColor(const Color &color) {
        _color = color;
        updateTextBox();
    }
} // engine