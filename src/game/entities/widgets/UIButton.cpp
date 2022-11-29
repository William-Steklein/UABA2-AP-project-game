#include "UIButton.h"
#include <engine/logging/Logger.h>

namespace game {
    UIButton::UIButton(engine::Transform transform, std::shared_ptr<engine::Vector2f> mouse_position,
                       const std::vector<std::shared_ptr<engine::IComponent>> &components)
            : engine::UIEntity(std::move(transform), components),
              _mouse_position(std::move(mouse_position)),
              _hit_box(std::make_shared<engine::HitBox>(engine::HitBox(getPosition(), {0, 0}))),
              _state(BUTTON_INACTIVE) {

    }

    void UIButton::handleInput(const InputEvent &input) {
        switch (_state) {
            case BUTTON_INACTIVE:
                if (input.type == InputEvent::Type::MOUSEMOVED && mouseCollides()) {
                    _state = BUTTON_HOVER;
                    LOGDEBUG("hover!");
                }
                break;

            case BUTTON_HOVER:
                if (input.type == InputEvent::Type::MOUSEMOVED && !mouseCollides()) {
                    _state = BUTTON_INACTIVE;
                    LOGDEBUG("not hover!");
                }

                if (input.type == InputEvent::Type::MOUSECLICK) {
                    _state = BUTTON_ACTIVE;
                    LOGDEBUG("active!");
                }
                break;

            default:
                break;
        }
    }

    const std::shared_ptr<engine::HitBox> &UIButton::getHitBox() const {
        return _hit_box;
    }

    bool UIButton::isActive() const {
        return _state == State::BUTTON_ACTIVE;
    }

    bool UIButton::mouseCollides() const {
        return _hit_box->collides(*_mouse_position);
    }
} // game