#include "State.hpp"

namespace st4code
{
    State::State(StateStack* stateStack) : pStateStack(stateStack)
    {
    }


	State::State(const State& state) : pStateStack(state.pStateStack)
	{
	}


    State::~State()
    {
    }


	const State& State::operator=(const State& state)
	{
		pStateStack = state.pStateStack;

		return (*this);
	}
}
