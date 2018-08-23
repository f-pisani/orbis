#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include <ctime>
#include "../st4code/Keyboard.hpp"
#include "../st4code/Mouse.hpp"

#include "GraphicsState.hpp"
#include "Orbis.hpp"
#include "GameStruct.hpp"

#define PI 3.14159265

class Orbis;
namespace GameOver
{
        enum class eSelectMenu
        {
                MainMenu, Exit, None
        };

        class State : public GraphicsState
        {
                public:
                        State(st4code::StateStack* stateStack, Orbis* orbis, GameStats gameStats);
                        ~State();

                protected:
                        void preUpdate();
                        void update();
                        void postUpdate();

                private:
                        Orbis* m_orbisMainWindow;
                        GameStats m_gameStats;
                        sf::Font g_ft;
                        sf::Texture g_txGameOverBackground;
                        sf::Texture g_txGameOverOrbisTypo;
                        sf::Sprite g_spGameOverBackground;
                        sf::Sprite g_spGameOverOrbisTypo;
                        sf::Text g_txtScore;
                        sf::Text g_txtScoreMax;
                        sf::Text g_txtMainMenu;
                        sf::Text g_txtExit;
                        eSelectMenu m_selectedMenu;

                        void updateTxtFade();
                        void mouseOverEvent();
                        void saveNewScoreMax();
                        int getScoreMax();
        };
}


#endif // GAMEOVER_HPP
