#include "StateStack.hpp"

namespace st4code
{
    StateStack::StateStack() : m_stateStack()
    {
    }


    StateStack::~StateStack()
    {
    	clear();
    }


    ///===================================================================================================
    /// PUBLIC
    ///===================================================================================================
    void StateStack::push(State* state)
    {
    	m_stateStack.push(state);
    }


    void StateStack::pop(size_t n)
    {
    	if(n<=size())
		{
			for(size_t i=0; i<n; i++)
				if(!empty())
					m_stateStack.pop();
		}
    }

	size_t StateStack::size()
	{
		return m_stateStack.size();
	}


	bool StateStack::empty()
	{
		return m_stateStack.empty();
	}


    void StateStack::exec()
    {
        if(!empty())
			m_stateStack.top()->exec();
    }


    void StateStack::clear()
    {
        for(size_t i=m_stateStack.size(); i>0; i--)
            m_stateStack.pop();
    }
}

