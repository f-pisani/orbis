#include "GraphicsState.hpp"

GraphicsState::GraphicsState(st4code::StateStack* stateStack) : State::State(stateStack)
{
}

GraphicsState::~GraphicsState()
{
}

///=====================================================================
/// PUBLIC
///=====================================================================
/////////////////////////////////////////////////////////////////////
// exec
void GraphicsState::exec()
{
	preUpdate();
	update();
	postUpdate();
}
