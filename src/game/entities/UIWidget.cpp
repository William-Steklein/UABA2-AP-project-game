#include "UIWidget.h"

namespace game {
    UIWidget::UIWidget(const engine::Transform &transform,
                       std::shared_ptr<engine::IViewComponent> view)
            : Entity(transform, std::move(view), nullptr, nullptr) {
        checkComponent(_view);

    }
} // game