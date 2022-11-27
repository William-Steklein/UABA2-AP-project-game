#ifndef GAME_ENGINE_SIDEBAR_H
#define GAME_ENGINE_SIDEBAR_H


#include "engine/entity/Entity.h"
#include "engine/entity/components/view/shape/IShapeComponent.h"

namespace engine {

    class SideBar : public Entity {
    public:
        SideBar(Transform transform, std::shared_ptr<IShapeComponent> rectangle);

        ~SideBar() = default;

        void update(double t, float dt) override;

    private:
        std::shared_ptr<IShapeComponent> _rectangle;
    };

} // engine

#endif //GAME_ENGINE_SIDEBAR_H
