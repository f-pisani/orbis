#ifndef PAUSE_HPP
#define PAUSE_HPP

#include <SFML/Graphics.hpp>
#include "../st4code/Keyboard.hpp"
#include "../st4code/Mouse.hpp"

#include "GraphicsState.hpp"
#include "Orbis.hpp"

class Orbis;
namespace Pause
{
	enum class eSelectMenu
	{
		Resume, Exit, None
	};

	class State : public GraphicsState
	{
		public:
			State(st4code::StateStack* stateStack, Orbis* orbis);
			~State();

		protected:
			void preUpdate();
			void update();
			void postUpdate();

		private:
			Orbis* m_orbisMainWindow;
			sf::Font g_ft;
			sf::Texture g_txPauseGameBackground;
			sf::Texture g_txPauseGameOrbisTypo;
			sf::Sprite g_spPauseGameBackground;
			sf::Sprite g_spPauseGameOrbisTypo;
			sf::Text g_txtResume;
			sf::Text g_txtExit;

			eSelectMenu m_selectedMenu;

			void mouseOverEvent();
			void updateTxtFade();
	};
}


#endif // PAUSE_HPP
