#ifndef GAME_ENGINE_IVIEWCOMPONENT_H
#define GAME_ENGINE_IVIEWCOMPONENT_H

#include <utility>

#include "engine/math/Vector2f.h"
#include "engine/entity/components/IComponent.h"
#include "engine/camera/Camera.h"

namespace engine {

    class IViewComponent : public IComponent {
    public:
        IViewComponent(std::weak_ptr<Camera> camera);

        void update(double t, float dt, Entity &entity) override = 0;

        virtual void setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v);

        virtual void setCamera(std::weak_ptr<Camera> camera);

    protected:
        Vector2f _size;

        unsigned int _texture_index;
        bool _mirror_h;
        bool _mirror_v;

        std::weak_ptr<Camera> _camera;
    };

} // engine

#endif //GAME_ENGINE_IVIEWCOMPONENT_H
