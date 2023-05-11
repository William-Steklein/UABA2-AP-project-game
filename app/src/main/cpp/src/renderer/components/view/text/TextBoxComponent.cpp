#include "TextBoxComponent.h"

namespace renderer {
    TextBoxComponent::TextBoxComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera,
                                       bool project_ui_space,
                                       std::shared_ptr<sf::Font> font)
            : ITextBoxComponent(size, std::move(camera), project_ui_space),
              _font(std::move(font)), _text_render(std::make_shared<sf::Text>()) {
        _text_render->setFont(*_font);

        updateTextRender();
    }

    void TextBoxComponent::update(double t, float dt) {
        updateTextRender();

        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }
        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        engine::Vector2f screen_position = camera_shared->projectCoordWorldToSubScreen(getPosition(),
                                                                                       _project_ui_space);
        _text_render->setPosition(screen_position.x, screen_position.y);

        engine::Vector2f scale = getScale();
        _text_render->setScale(scale.x, scale.y);

        _text_render->setRotation(engine::toDegree(getRotation()));

    }

    std::shared_ptr<sf::Text> TextBoxComponent::getTextRender() {
        return _text_render;
    }

    void TextBoxComponent::updateTextBox() {
        updateTextRender();
    }

    void TextBoxComponent::updateTextRender() {
        _text_render->setCharacterSize(
                static_cast<unsigned int>(_camera.lock()->projectVerticalSizeWorldToSubScreen(_font_size)));
        _text_render->setFillColor(sf::Color(_fillcolor.r, _fillcolor.g, _fillcolor.b, _fillcolor.a));

        _text_render->setString(_text);
        sf::FloatRect text_rect = _text_render->getLocalBounds();
        _text_render->setOrigin(text_rect.left + text_rect.width / 2, text_rect.top + text_rect.height / 2);
    }
} // renderer