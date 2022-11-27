#include "SideBar.h"

namespace engine {
    SideBar::SideBar(Transform transform, std::shared_ptr<IShapeComponent> rectangle)
            : Entity(std::move(transform)), _rectangle(std::move(rectangle)) {

    }

    void SideBar::update(double t, float dt) {
        Entity::update(t, dt);
    }
} // engine