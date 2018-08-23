#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include "../st4code/Keyboard.hpp"
#include "../st4code/Mouse.hpp"

#include "Orbis.hpp"
#include "GraphicsState.hpp"
#include "Pause.hpp"
#include "GameOver.hpp"
#include "GameStruct.hpp"

#define PI 3.14159265

class Orbis;
namespace Game
{
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
                        sf::Texture g_txMainGameDisc_1;
                        sf::Texture g_txMainGameDisc_2;
                        sf::Texture g_txMainGameBullet;
                        sf::Texture g_txMainGameDiscInvader_1;
                        sf::Sprite g_spMainGameDisc_1;
                        sf::Sprite g_spMainGameDisc_2;
                        sf::Sprite g_spMainGameBullet;
                        sf::Sprite g_spMainGameInvader;
                        sf::Text g_txtScore;
                        bool m_gameIsPaused;
                        bool m_gameOver;
                        GameStats m_gameStats;
                        sf::Clock m_gameClock;
                        sf::Time m_gameTimeElapsed;
                        int m_disc2Position;
                        int m_disc2PositionTarget;
                        float m_disc2Speed;
                        float m_disc2Recoil;
                        std::vector<Bullet> m_bullets;
                        std::vector<Invader> m_invaders;
                        std::vector<SpawnRules> m_spawnRules;
                        // animations
                        void updateDiscAnimation();
                        void updateScoreAnimation();
                        // bullets
                        void updateBullets();
                        void drawBullets();
                        // invaders
                        void spawnInvaders();
                        void createInvader(float speed, int score);
                        void updateInvaders();
                        void drawInvaders();
                        //collision
                        void collisionSolver();
        };
}



#endif // GAME_HPP
