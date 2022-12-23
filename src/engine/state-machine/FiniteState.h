#ifndef GAME_ENGINE_FINITESTATE_H
#define GAME_ENGINE_FINITESTATE_H

#include "engine/state-machine/State.h"

namespace engine {

    template<typename FiniteStateMachine, class BaseState, class Input>
    class FiniteState : public State<FiniteStateMachine, Input> {
    public:
        FiniteState(FiniteStateMachine &state_machine, std::unique_ptr<BaseState> &state)
                : State<FiniteStateMachine, Input>(state_machine), _state(state) {}

        template<class ConcreteState>
        static void init(FiniteStateMachine &state_machine, std::unique_ptr<BaseState> &state) {
            if (state) {
                state->exit();
            }
            state = std::unique_ptr<BaseState>(new ConcreteState(state_machine, state));
            state->enter();
        }

    protected:
        template<class ConcreteState>
        void set() {
            init<ConcreteState>(this->_state_machine, _state);
        }

    private:
        std::unique_ptr<BaseState> &_state;
    };

} // engine

#endif //GAME_ENGINE_FINITESTATE_H
