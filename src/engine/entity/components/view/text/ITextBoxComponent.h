#ifndef GAME_ENGINE_ITEXTBOXCOMPONENT_H
#define GAME_ENGINE_ITEXTBOXCOMPONENT_H


#include "engine/entity/components/view/shape/IShapeComponent.h"

namespace engine {

    class ITextBoxComponent : public IShapeComponent {
    public:
        ITextBoxComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space);

        ~ITextBoxComponent() = default;

        void update(double t, float dt, Entity &entity) override;

        const std::string &getText() const;

        void setText(const std::string &text);

        float getFontSize() const;

        void setFontSize(float font_size);

    protected:
        std::string _text;
        float _font_size;

        void updateShape() override;

        virtual void updateTextBox() = 0;
    };

} // engine

#endif //GAME_ENGINE_ITEXTBOXCOMPONENT_H
