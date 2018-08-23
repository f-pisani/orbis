#ifndef RECORD_HPP
#define RECORD_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include <ctime>
#include "../st4code/Keyboard.hpp"
#include "../st4code/Mouse.hpp"

#include "GraphicsState.hpp"
#include "Orbis.hpp"

#define PI 3.14159265

class Orbis;
namespace Record
{
	enum class eSelectMenu
	{
		MainMenu, None
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
			sf::Texture g_txRecordOrbisTypo;
			sf::Sprite g_spRecordOrbisTypo;
			sf::Text g_txtScore;
			sf::Text g_txtMainMenu;
			eSelectMenu m_selectedMenu;

			void updateTxtFade();
			void mouseOverEvent();
			int getScoreMax();
	};
}
#endif // RECORD_HPP
