#ifndef GAME_ENGINE_BUTTONSTATE_H
#define GAME_ENGINE_BUTTONSTATE_H

#include <engine/state-machine/FiniteState.h>
#include "game/entities/ui/button/Button.h"

namespace game {

    struct Inactive;
    struct Hover;
    struct Clicking;
    struct Clicked;

    struct ButtonState : public engine::FiniteState<Button, ButtonState, InputEvent> {
        using FiniteState::FiniteState;

        virtual bool isActive() const {
            return false;
        };

        virtual bool isClicking() const {
            return false;
        }
    };

    struct Inactive : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("default", false);

            if (_state_machine.mouseCollides()) {
                set<Hover>();
            }
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                case InputEvent::Type::MOUSEMOVED:
                    if (_state_machine.mouseCollides()) {
                        set<Hover>();
                    }
                    break;

                case InputEvent::Type::MOUSECLICK:
                    if (input.state == InputEvent::State::ENTERED &&
                        _state_machine.mouseCollides()) {
                        set<Clicking>();
                    }
                    break;

                case InputEvent::Type::TOUCH:
                    if (input.state == InputEvent::State::ENTERED &&
                        _state_machine.touchCollides(Range2DToVector2f(input.range_2d))) {
                        set<Clicking>();
                    }
                    break;

                default:
                    break;
            }
        }
    };

    struct Hover : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("hover", false);
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                case InputEvent::Type::MOUSEMOVED:
                    if (!_state_machine.mouseCollides()) {
                        set<Inactive>();
                    }
                    break;

                case InputEvent::Type::MOUSECLICK:
                    if (input.state == InputEvent::State::ENTERED) {
                        set<Clicking>();
                    }
                    break;

                case InputEvent::Type::TOUCH:
                    if (input.state == InputEvent::State::ENTERED &&
                        _state_machine.touchCollides(Range2DToVector2f(input.range_2d))) {
                        set<Clicking>();
                    }
                    break;

                default:
                    break;
            }
        }
    };

    struct Clicking : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("clicking", false);
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                case InputEvent::Type::MOUSEMOVED:
                    if (!_state_machine.mouseCollides()) {
                        set<Inactive>();
                    }
                    break;

                case InputEvent::Type::MOUSECLICK:
                    if (input.state == InputEvent::State::EXITED) {
                        set<Clicked>();
                    }
                    break;

                case InputEvent::Type::TOUCH:
                    if (input.state == InputEvent::State::EXITED &&
                        _state_machine.touchCollides(Range2DToVector2f(input.range_2d))) {
                        set<Clicked>();
                    }
                    break;

                default:
                    break;
            }
        }

        bool isClicking() const override {
            return true;
        }
    };

    struct Clicked : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("default", false);
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                default:
                    break;
            }
        }

        bool isActive() const override {
            return true;
        }
    };

} // game

#endif //GAME_ENGINE_BUTTONSTATE_H
