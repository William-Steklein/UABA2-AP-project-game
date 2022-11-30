#ifndef GAME_ENGINE_ISHAPECOMPONENT_H
#define GAME_ENGINE_ISHAPECOMPONENT_H


#include "engine/entity/components/view/IViewComponent.h"
#include "engine/Color.h"

namespace engine {

    class IShapeComponent : public IViewComponent {
    public:
        const Color &getFillcolor() const;

        void setFillcolor(const Color &fillcolor);

        const Color &getOutlineColor() const;

        void setOutlineColor(const Color &outline_color);

        float getOutlineThickness() const;

        void setOutlineThickness(float outline_thickness);

    protected:
        Color _fillcolor;
        Color _outline_color;
        float _outline_thickness;

        IShapeComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space);

        virtual void updateShape() = 0;
    };

} // engine

#endif //GAME_ENGINE_ISHAPECOMPONENT_H
