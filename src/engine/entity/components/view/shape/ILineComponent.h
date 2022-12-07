#ifndef GAME_ENGINE_IRECTANCLECOMPONENT_H
#define GAME_ENGINE_IRECTANCLECOMPONENT_H


#include <cmath>

#include "IShapeComponent.h"

namespace engine {

    class ILineComponent : public IShapeComponent {
    public:
        ILineComponent(std::weak_ptr<Camera> camera, bool project_ui_space);

        ~ILineComponent() override = default;

        const Vector2f &getOrigin() const;

        void setOrigin(const Vector2f &origin);

        const Vector2f &getEnd() const;

        void setEnd(const Vector2f &end);

        void setLine(const Vector2f &origin, const Vector2f &end);

        float getLineThickness() const;

        void setLineThickness(float line_thickness);

        Vector2f getLineVector() const;

        void updateLineSize();

        Vector2f getPosition() override;

        float getRotation() override;

    protected:
        Vector2f _origin;
        Vector2f _end;
        float _line_thickness;

        float _shape_rotation;

        void updateShapeRotation();
    };

} // engine

#endif //GAME_ENGINE_IRECTANCLECOMPONENT_H
