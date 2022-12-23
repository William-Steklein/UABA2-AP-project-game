#include "Button.h"
#include "engine/logging/Logger.h"
#include "ButtonState.h"

namespace game {
    Button::Button(engine::Transform transform, const engine::Vector2f &hit_box_size,
                   std::shared_ptr<engine::Vector2f> mouse_position,
                   std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite,
                   const std::vector<std::shared_ptr<engine::IComponent>> &components)
            : engine::UIEntity(std::move(transform), components),
              _mouse_position(std::move(mouse_position)),
              _hit_box(std::make_shared<engine::HitBox>(engine::HitBox(hit_box_size))),
              _animated_sprite(std::move(animated_sprite)), _state(nullptr) {
        addComponents({_animated_sprite, _hit_box});

        ButtonState::init<Inactive>(*this, _state);
    }

    void Button::handleInput(const InputEvent &input) {
        _state->handleInput(input);
    }

    bool Button::isActive() const {
        return _state->isActive();
    }

    bool Button::mouseCollides() const {
        return _hit_box->collides(*_mouse_position);
    }

    void Button::reset() {
        ButtonState::init<Inactive>(*this, _state);
    }
} // game