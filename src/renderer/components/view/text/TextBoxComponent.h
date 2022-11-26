#ifndef GAME_ENGINE_TEXTBOXCOMPONENT_H
#define GAME_ENGINE_TEXTBOXCOMPONENT_H


#include <SFML/Graphics/Text.hpp>

#include "engine/entity/components/view/text/ITextBoxComponent.h"
#include "engine/math/math_utils.h"

namespace renderer {

    class TextBoxComponent : public engine::ITextBoxComponent {
    public:
        TextBoxComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera,
                         std::shared_ptr<sf::Font> font);

        ~TextBoxComponent() = default;

        void update(double t, float dt, engine::Entity &entity) override;

        std::shared_ptr<sf::Text> getTextRender();

    private:
        std::shared_ptr<sf::Font> _font;
        std::shared_ptr<sf::Text> _text_render;

        void updateTextBox() override;

        void updateTextRender();
    };

} // renderer

#endif //GAME_ENGINE_TEXTBOXCOMPONENT_H
