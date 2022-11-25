#ifndef GAME_ENGINE_UIWIDGET_H
#define GAME_ENGINE_UIWIDGET_H


#include <engine/entity/Entity.h>

namespace game {

    class UIWidget : public engine::Entity {
    public:
        UIWidget(const engine::Transform &transform,
                 std::shared_ptr<engine::IViewComponent> view);

        ~UIWidget() = default;

    private:

    };

} // game

#endif //GAME_ENGINE_UIWIDGET_H
