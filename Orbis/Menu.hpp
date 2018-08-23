#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "../st4code/Keyboard.hpp"
#include "../st4code/Mouse.hpp"

#include "GraphicsState.hpp"
#include "Orbis.hpp"
#include "Game.hpp"
#include "Record.hpp"

#define PI 3.14159265

class Orbis;
namespace Menu
{
        enum class eSelectMenu
        {
            Play, Record, Credit, Exit
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
                        sf::Texture g_txMainMenuOrbisTypo;
                        sf::Texture g_txMainMenuDisc_1;
                        sf::Texture g_txMainMenuDisc_2;
                        sf::Sprite g_spMainMenuOrbisTypo;
                        sf::Sprite g_spMainMenuDisc_1;
                        sf::Sprite g_spMainMenuDisc_2;
                        sf::Text g_txtPlay;
                        sf::Text g_txtRecord;
                        sf::Text g_txtCredit;
                        sf::Text g_txtExit;
                        eSelectMenu m_selectedMenu;
                        int m_angleDisc2;

                        void mouseOverEvent();
                        void updateDiscAnimation();
                        void updateTxtFade();
        };
}

#endif // MENU_HPP
