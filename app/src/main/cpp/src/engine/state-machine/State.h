#ifndef GAME_ENGINE_STATE_H
#define GAME_ENGINE_STATE_H

#include <memory>
#include <stack>
#include <stdexcept>

namespace engine {

    /**
     * Generic interface state class that implements the state design pattern.
     * @tparam StateMachine state machine class that will use concrete states of this class
     * @tparam Input input type used for the state machine
     *
     * Used as reference:
     * - "https://codereview.stackexchange.com/questions/40686/state-pattern-c-template"
     * - "https://gameprogrammingpatterns.com/state.html"
     */
    template<typename StateMachine, class Input>
    class State {
    public:
        virtual ~State() = default;

        virtual void enter() {}

        virtual void exit() {}

        virtual void pause() {}

        virtual void resume() {}

        virtual void reset() { enter(); }

        virtual void graphicsUpdate(double t, float dt) {}

        virtual void physicsUpdate(double t, float dt) {}

        virtual void handleInput(const Input &input) {}

    protected:
        StateMachine &_state_machine;

        State(StateMachine &state_machine) : _state_machine(state_machine) {}
    };

} // engine

#endif //GAME_ENGINE_STATE_H
