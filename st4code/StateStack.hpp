#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <memory>
#include <stack>
#include "State.hpp"

namespace st4code
{
    class State;
    class StateStack
    {
        public:
            StateStack();
            ~StateStack();
            void push(State* state);
            void pop(size_t n=1);
            size_t size();
            bool empty();
            void exec();
            void clear();

        private:
            std::stack<State*> m_stateStack;
    };
}


#endif // STATESTACK_HPP
