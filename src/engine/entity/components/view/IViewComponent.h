#ifndef GAME_ENGINE_IVIEWCOMPONENT_H
#define GAME_ENGINE_IVIEWCOMPONENT_H


#include "engine/entity/components/IComponent.h"
#include "engine/entity/Entity.h"
#include "engine/camera/Camera.h"

namespace engine {

    class IViewComponent : public IComponent {
    public:
        IViewComponent(const Vector2f &size, std::weak_ptr<Camera> camera, bool project_ui_space);

        ~IViewComponent() = default;

        const Vector2f &getSize() const;

        virtual void setSize(const Vector2f &size);

        const std::weak_ptr<Camera> &getCamera() const;

        void setCamera(const std::weak_ptr<Camera> &camera);

        bool isVisible() const;

        void setVisible(bool visible);

        Vector2f getScale() override;

    protected:
        Vector2f _size;
        std::weak_ptr<Camera> _camera;
        bool _project_ui_space;
        bool _visible;

        Vector2f _offset;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENT_H
