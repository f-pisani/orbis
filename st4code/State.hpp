#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include "StateStack.hpp"

namespace st4code
{
    class StateStack;
    class State
    {
        public:
            State(StateStack* stateStack);
            State(const State& state);
            const State& operator=(const State& state);
            virtual ~State();
            virtual void exec()=0;

        protected:
            std::shared_ptr<StateStack> pStateStack;
    };
}


#endif // STATE_HPP
