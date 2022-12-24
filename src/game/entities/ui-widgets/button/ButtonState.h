#ifndef GAME_ENGINE_BUTTONSTATE_H
#define GAME_ENGINE_BUTTONSTATE_H

#include <engine/state-machine/FiniteState.h>
#include "game/entities/ui-widgets/button/Button.h"

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
    };

    struct Inactive : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("default");

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

                default:
                    break;
            }
        }
    };

    struct Hover : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("hover");
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                case InputEvent::Type::MOUSEMOVED:
                    if (!_state_machine.mouseCollides()) {
                        set<Inactive>();
                    }
                    break;

                case InputEvent::Type::MOUSECLICK:
//                    case InputEvent::Type::ACCEPT:
                    if (input.state == InputEvent::State::ENTERED) {
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
            _state_machine._animated_sprite->start("clicking");
        }

        void handleInput(const InputEvent &input) override {
            switch (input.type) {
                case InputEvent::Type::MOUSEMOVED:
                    if (!_state_machine.mouseCollides()) {
                        set<Inactive>();
                    }
                    break;

                case InputEvent::Type::MOUSECLICK:
//                    case InputEvent::Type::ACCEPT:
                    if (input.state == InputEvent::State::EXITED) {
                        set<Clicked>();
                    }
                    break;

                default:
                    break;
            }
        }
    };

    struct Clicked : public ButtonState {
        using ButtonState::ButtonState;

        void enter() override {
            _state_machine._animated_sprite->start("default");
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
