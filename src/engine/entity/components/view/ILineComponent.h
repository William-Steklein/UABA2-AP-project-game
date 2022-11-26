#ifndef GAME_ENGINE_IRECTANCLECOMPONENT_H
#define GAME_ENGINE_IRECTANCLECOMPONENT_H


#include <cmath>

#include "engine/entity/components/view/IShapeComponent.h"

namespace engine {

    class ILineComponent : public IShapeComponent {
    public:
        ILineComponent(const Vector2f &size, std::weak_ptr<Camera> camera,
                       const Vector2f &origin, const Vector2f &end);

        ~ILineComponent() = default;

        const Vector2f &getOrigin() const;

        void setOrigin(const Vector2f &origin);

        const Vector2f &getEnd() const;

        void setEnd(const Vector2f &end);

        float getLineThickness() const;

        void setLineThickness(float line_thickness);

    protected:
        Vector2f _origin;
        Vector2f _end;
        float _line_thickness;

        float _shape_rotation;

        float getShapeRotation();
    };

} // engine

#endif //GAME_ENGINE_IRECTANCLECOMPONENT_H
