#include "UIButton.h"
#include <engine/logging/Logger.h>

namespace game {
    UIButton::UIButton(engine::Transform transform, const engine::Vector2f &hit_box_size,
                       std::shared_ptr<engine::Vector2f> mouse_position,
                       std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite,
                       const std::vector<std::shared_ptr<engine::IComponent>> &components)
            : engine::UIEntity(std::move(transform), components),
              _mouse_position(std::move(mouse_position)),
              _hit_box(std::make_shared<engine::HitBox>(engine::HitBox(hit_box_size))),
              _state(BUTTON_INACTIVE),
              _animated_sprite(std::move(animated_sprite)) {
        addComponents({_animated_sprite, _hit_box});

        reset();
    }

    void UIButton::handleInput(const InputEvent &input) {
        switch (_state) {
            case BUTTON_INACTIVE:
                if (input.type == InputEvent::Type::MOUSEMOVED && mouseCollides()) {
                    _state = BUTTON_HOVER;
                    _animated_sprite->start("hover");
//                    LOGDEBUG("hover!");
                }
                break;

            case BUTTON_HOVER:
                if (input.type == InputEvent::Type::MOUSEMOVED && !mouseCollides()) {
                    _state = BUTTON_INACTIVE;
                    _animated_sprite->start("default");
//                    LOGDEBUG("NOT hover!");
                }

                if ((input.type == InputEvent::Type::MOUSECLICK || input.type == InputEvent::Type::ACCEPT) &&
                    input.state_enter) {
                    _state = BUTTON_CLICKING;
                    _animated_sprite->start("clicking");
//                    LOGDEBUG("clicking!");
                }
                break;

            case BUTTON_CLICKING:
                if (input.type == InputEvent::Type::MOUSEMOVED && !mouseCollides()) {
                    _state = BUTTON_INACTIVE;
                    _animated_sprite->start("default");
//                    LOGDEBUG("NOT hover and NOT clicking!");
                }

                if ((input.type == InputEvent::Type::MOUSECLICK || input.type == InputEvent::Type::ACCEPT) &&
                    !input.state_enter) {
                    _state = BUTTON_ACTIVE;
//                    _state = BUTTON_CLICKED;
//                    LOGDEBUG("active!");
                }

//            case BUTTON_CLICKED:
//                break;

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

    void UIButton::reset() {
        if (mouseCollides()) {
            _state = BUTTON_HOVER;
            _animated_sprite->start("hover");
        } else {
            _animated_sprite->start("default");
        }
    }

    void UIButton::setKeyboardActive() {
        if (_state == BUTTON_INACTIVE) {
            _state = BUTTON_HOVER;
            _animated_sprite->start("hover");
        }
    }

    void UIButton::setKeyboardInactive() {
        if (_state == BUTTON_HOVER && !mouseCollides()) {
            _state = BUTTON_INACTIVE;
            _animated_sprite->start("default");
        }
    }
} // game