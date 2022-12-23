#ifndef GAME_ENGINE_PUSHDOWNSTATE_H
#define GAME_ENGINE_PUSHDOWNSTATE_H

#include "engine/state-machine/State.h"

namespace engine {

    template<typename PushdownAutomaton, class BaseState, class Input>
    class PushdownState : public State<PushdownAutomaton, Input> {
    public:
        PushdownState(PushdownAutomaton &state_machine, std::stack<std::unique_ptr<BaseState>> &states)
                : State<PushdownAutomaton, Input>(state_machine), _states(states) {}

        template<class ConcreteState>
        static void init(PushdownAutomaton &state_machine, std::stack<std::unique_ptr<BaseState>> &states) {
            if (!states.empty()) {
                states.top()->exit();
                states.pop();
            }
            states.push(std::unique_ptr<BaseState>(new ConcreteState(state_machine, states)));
            states.top()->enter();
        }

        static void _pop(std::stack<std::unique_ptr<BaseState>> &states) {
            if (states.size() <= 1) {
                throw std::runtime_error("Popping state stack with 1 element");
            }
            states.top()->exit();
            states.pop();
        }

        static void _popAndResume(std::stack<std::unique_ptr<BaseState>> &states) {
            _pop(states);
            states.top()->resume();
        }

        static void _popAndReset(std::stack<std::unique_ptr<BaseState>> &states) {
            _pop(states);
            states.top()->reset();
        }

        template<class ConcreteState>
        static void _popAndSet(PushdownAutomaton &state_machine, std::stack<std::unique_ptr<BaseState>> &states) {
            _pop(states);
            init<ConcreteState>(state_machine, states);
        }

    protected:
        template<class ConcreteState>
        void set() {
            init<ConcreteState>(this->_state_machine, _states);
        }

        template<class ConcreteState>
        void push() {
            this->pause();
            _states.push(std::unique_ptr<BaseState>(new ConcreteState(this->_state_machine, _states)));
            _states.top()->enter();
        }

        void pop() {
            _popAndResume(_states);
        }

        void popAndReset() {
            _popAndReset(_states);
        }

        template<class ConcreteState>
        void popAndSet() {
            _popAndSet<ConcreteState>(this->_state_machine, _states);
        }

    private:
        std::stack<std::unique_ptr<BaseState>> &_states;
    };

} // engine

#endif //GAME_ENGINE_PUSHDOWNSTATE_H
