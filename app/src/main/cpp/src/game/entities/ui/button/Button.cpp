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

    void Button::setPosition(const engine::Vector2f &position) {
        engine::UIEntity::setPosition(position);

        _resendMouseMovedInput();
    }

    void Button::setScale(const engine::Vector2f &scale) {
        engine::UIEntity::setScale(scale);

        _resendMouseMovedInput();
    }

    void Button::handleInput(const InputEvent &input) {
        _state->handleInput(input);
    }

    bool Button::isClicking() const {
        return _state->isClicking();
    }

    bool Button::isActive() const {
        return _state->isActive();
    }

    bool Button::mouseCollides() const {
        return _hit_box->collides(*_mouse_position);
    }

    bool Button::touchCollides(const engine::Vector2f& touch_position) const {
        return _hit_box->collides(touch_position);
    }

    void Button::reset() {
        ButtonState::init<Inactive>(*this, _state);
    }

    void Button::_resendMouseMovedInput() {
        game::InputEvent input{};

        input.type = game::InputEvent::Type::MOUSEMOVED;
        input.state = game::InputEvent::State::ACTIVE;

        _state->handleInput(input);
    }
} // game