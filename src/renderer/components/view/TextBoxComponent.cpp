#include "TextBoxComponent.h"

namespace renderer {
    TextBoxComponent::TextBoxComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera,
                                       std::shared_ptr<sf::Font> font,
                                       float font_size, const engine::Color &color, const std::string &text)
            : ITextBoxComponent(size, std::move(camera), font_size, color, text),
              _font(std::move(font)), _text_render(std::make_shared<sf::Text>()) {
        _text_render->setFont(*_font);

        updateTextRender();
    }

    void TextBoxComponent::update(double t, float dt, engine::Entity &entity) {
        ITextBoxComponent::update(t, dt, entity);

        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }
        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        engine::Vector2f screen_position = camera_shared->projectCoordWorldToSubScreen(entity.getPosition());
        _text_render->setPosition(screen_position.x, screen_position.y);

        _text_render->setScale(entity.getScale().x, entity.getScale().y);

        _text_render->setRotation(engine::toDegree(entity.getRotation()));

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
        _text_render->setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a));

        _text_render->setString(_text);
        sf::FloatRect text_rect = _text_render->getLocalBounds();
        _text_render->setOrigin(text_rect.left + text_rect.width / 2, text_rect.top + text_rect.height / 2);
    }
} // renderer