#ifndef GAME_ENGINE_IVIEWCOMPONENT_H
#define GAME_ENGINE_IVIEWCOMPONENT_H


#include "engine/entity/components/IComponent.h"
#include "engine/camera/Camera.h"

namespace engine {

    class IViewComponent : public IComponent {
    public:
        IViewComponent(const Vector2f &size, std::weak_ptr<Camera> camera);

        ~IViewComponent() = default;

        const Vector2f &getSize() const;

        void setSize(const Vector2f &size);

        const std::weak_ptr<Camera> &getCamera() const;

        void setCamera(const std::weak_ptr<Camera> &camera);

    protected:
        Vector2f _size;
        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENT_H
