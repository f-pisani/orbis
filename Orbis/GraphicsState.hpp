#ifndef GRAPHICSSTATE_HPP
#define GRAPHICSSTATE_HPP

#include "../st4code/State.hpp"

class GraphicsState : public st4code::State
{
	public:
		GraphicsState(st4code::StateStack* stateStack);
		~GraphicsState();
		void exec();

	protected:
		virtual void preUpdate()=0;
		virtual void update()=0;
		virtual void postUpdate()=0;
};

#endif // GRAPHICSSTATE_HPP
