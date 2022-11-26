#ifndef GAME_ENGINE_ITEXTBOXCOMPONENT_H
#define GAME_ENGINE_ITEXTBOXCOMPONENT_H


#include "engine/entity/components/view/IViewComponent.h"
#include "engine/Color.h"

namespace engine {

    class ITextBoxComponent : public IViewComponent {
    public:
        ITextBoxComponent(const Vector2f &size, std::weak_ptr<Camera> camera,
                          float font_size, const Color &color, const std::string &text);

        ~ITextBoxComponent() = default;

        void update(double t, float dt, Entity &entity) override;

        const std::string &getText() const;

        void setText(const std::string &text);

        float getFontSize() const;

        void setFontSize(float font_size);

        const Color &getColor() const;

        void setColor(const Color &color);

    protected:
        std::string _text;
        float _font_size;
        Color _color;

        virtual void updateTextBox() = 0;
    };

} // engine

#endif //GAME_ENGINE_ITEXTBOXCOMPONENT_H
