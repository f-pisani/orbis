#include "Game.hpp"

Game::State::State(st4code::StateStack* stateStack, Orbis* orbis) :
	GraphicsState::GraphicsState(stateStack), m_orbisMainWindow(orbis),
	g_ft(), g_txMainGameDisc_1(), g_txMainGameDisc_2(), g_txMainGameBullet(), g_txMainGameDiscInvader_1(),
	g_spMainGameDisc_1(), g_spMainGameDisc_2(), g_spMainGameBullet(), g_spMainGameInvader(), g_txtScore(),
	m_gameIsPaused(false), m_gameOver(false), m_gameStats(), m_gameClock(), m_gameTimeElapsed(), m_disc2Position(0), m_disc2PositionTarget(0), m_disc2Speed(4.0f), m_disc2Recoil(70.f), m_bullets(),
	m_invaders(), m_spawnRules()
{
	// sf::Font
		g_ft.loadFromFile("data/Neuropol.ttf");
	// sf::Texture
		// Disc 1
		g_txMainGameDisc_1.loadFromFile("data/MainGameDisc_1.png");
		g_txMainGameDisc_1.setSmooth(true);
		// Disc 2
		g_txMainGameDisc_2.loadFromFile("data/MainGameDisc_2.png");
		g_txMainGameDisc_2.setSmooth(true);
		// Bullet
		g_txMainGameBullet.loadFromFile("data/MainGameBullet.png");
		g_txMainGameBullet.setSmooth(true);
		// Invader
		g_txMainGameDiscInvader_1.loadFromFile("data/MainGameDiscInvader_1.png");
		g_txMainGameBullet.setSmooth(true);
	// sf::Sprite
		// Disc 1
		g_spMainGameDisc_1.setTexture(g_txMainGameDisc_1);
		g_spMainGameDisc_1.setOrigin(g_spMainGameDisc_1.getGlobalBounds().width/2,
									 g_spMainGameDisc_1.getGlobalBounds().height/2);
		g_spMainGameDisc_1.setPosition(m_orbisMainWindow->getSize().x/2,
									   m_orbisMainWindow->getSize().y/2);
		g_spMainGameDisc_1.setColor(sf::Color(255, 255, 255));
		// Disc 2
		g_spMainGameDisc_2.setTexture(g_txMainGameDisc_2);
		g_spMainGameDisc_2.setOrigin(g_spMainGameDisc_2.getGlobalBounds().width/2,
									 g_spMainGameDisc_2.getGlobalBounds().height/2);
		// Bullet
		g_spMainGameBullet.setTexture(g_txMainGameBullet);
		g_spMainGameBullet.setOrigin(g_spMainGameBullet.getGlobalBounds().width/2,
									 g_spMainGameBullet.getGlobalBounds().height/2);
		// Invader
		g_spMainGameInvader.setTexture(g_txMainGameDiscInvader_1);
		g_spMainGameInvader.setOrigin(g_spMainGameInvader.getGlobalBounds().width/2,
									  g_spMainGameInvader.getGlobalBounds().height/2);
	// sf::Text
		// Score
		g_txtScore.setString("0");
		g_txtScore.setCharacterSize(32);
		g_txtScore.setFont(g_ft);
		g_txtScore.setPosition(5, 0);
	// Spawner Rules || < time; spawn limit; spawn interval; invader speed; invader score;
	// the last entrie is for else statement (after the last < time)
	m_spawnRules.push_back(SpawnRules(10000, 4, 800, 2, 50));
	m_spawnRules.push_back(SpawnRules(20000, 8, 800, 3, 100));
	m_spawnRules.push_back(SpawnRules(30000, 8, 700, 4, 150));
	m_spawnRules.push_back(SpawnRules(40000, 12, 700, 5, 300));
	m_spawnRules.push_back(SpawnRules(50000, 12, 600, 6, 400));
	m_spawnRules.push_back(SpawnRules(60000, 16, 600, 6, 800));
	m_spawnRules.push_back(SpawnRules(0,    20, 500, 6, 1000));
}


Game::State::~State()
{
}




///=====================================================================
/// PROTECTED
///=====================================================================
/////////////////////////////////////////////////////////////////////
// preUpdate
void Game::State::preUpdate()
{
	if(!m_gameOver)
	{
		updateDiscAnimation(); // Animation des disques
		updateScoreAnimation(); // Animation du score
		collisionSolver(); // Gestion des collisions
		updateBullets(); // Mise à jour de la position des balles
		updateInvaders(); // Mise à jour de la position des envahisseurs
		spawnInvaders(); // Spawn des envahisseurs
	}
	else
	{
        pStateStack->pop(1);
        pStateStack->push(new GameOver::State(pStateStack.get(), m_orbisMainWindow, m_gameStats));
	}
}


/////////////////////////////////////////////////////////////////////
// update
void Game::State::update()
{
    m_orbisMainWindow->clear(sf::Color(10, 15, 40));
        m_orbisMainWindow->draw(g_spMainGameDisc_1);
        m_orbisMainWindow->draw(g_spMainGameDisc_2);
        drawBullets(); // Affichage des balles
        drawInvaders(); // Affichage des envahisseurs
		m_orbisMainWindow->draw(g_txtScore);
    m_orbisMainWindow->display();
}


/////////////////////////////////////////////////////////////////////
// postUpdate
void Game::State::postUpdate()
{
	// Mise à jour du timer interne
	if(!m_gameIsPaused)
	{
		m_gameTimeElapsed += m_gameClock.getElapsedTime();
		m_gameClock.restart();
	}
	else
	{
		m_gameIsPaused = false;
		m_gameClock.restart();
	}
	// Perte de focus
	if(!m_gameIsPaused && !m_orbisMainWindow->isWindowFocus())
		m_gameIsPaused = true;
	// Jeu en pause
	if(st4code::Keyboard::isKeyReleased(sf::Keyboard::Escape))
	{
		pStateStack->push(new Pause::State(pStateStack.get(), m_orbisMainWindow));
		m_gameIsPaused = true;
	}
	// Mise à jour de la position du joueur
	m_disc2Position = atan2((st4code::Mouse::getPosition(*m_orbisMainWindow).y - g_spMainGameDisc_1.getPosition().y), (st4code::Mouse::getPosition(*m_orbisMainWindow).x - g_spMainGameDisc_1.getPosition().x))*180/PI;
	// Tir
	if(st4code::Mouse::isButtonPressed(sf::Mouse::Left))
		if(m_bullets.size() == 0 || (m_gameTimeElapsed.asMilliseconds()-m_bullets.back().time()) >= 40)
			m_bullets.push_back(Bullet(m_gameTimeElapsed.asMilliseconds(), m_disc2Position, g_spMainGameDisc_2.getPosition()));
}




///=====================================================================
/// PRIVATE
///=====================================================================
/// ANIMATION
/////////////////////////////////////////////////////////////////////
// updateDiscAnimation
void Game::State::updateDiscAnimation()
{
	// Effet de recul lors du tir
	if(st4code::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(m_disc2Recoil > 66.f)
			m_disc2Recoil -= 0.5f;
		else if(m_disc2Recoil == 66.f)
			m_disc2Recoil += 3.f;
	}
	else
	{
		if(m_disc2Recoil < 70.f)
			m_disc2Recoil += 1.f;
	}
    g_spMainGameDisc_2.setPosition(g_spMainGameDisc_1.getPosition().x+m_disc2Recoil*std::cos(m_disc2Position*PI/180),
								   g_spMainGameDisc_1.getPosition().y+m_disc2Recoil*std::sin(m_disc2Position*PI/180));

    // Rotation des disques
    g_spMainGameDisc_1.rotate(0.5f);
    g_spMainGameDisc_2.rotate(-0.5f);
}


/////////////////////////////////////////////////////////////////////
// updateScoreAnimation
void Game::State::updateScoreAnimation()
{
    // Mis à jour de l'affichage du score
    int displayedScore = stringToInt(g_txtScore.getString());
    int actualVSdisplayedScore = (m_gameStats.score-displayedScore);
    if(actualVSdisplayedScore != 0 && actualVSdisplayedScore > 1000)
		displayedScore += 100;
	else if(actualVSdisplayedScore != 0 && actualVSdisplayedScore <= 10)
		displayedScore += 1;
	else if(actualVSdisplayedScore != 0 && actualVSdisplayedScore <= 50)
		displayedScore += 2;
	else if(actualVSdisplayedScore != 0 && actualVSdisplayedScore <= 210)
		displayedScore += 8;
	else if(actualVSdisplayedScore != 0 && actualVSdisplayedScore <= 1100)
		displayedScore += 55;

	g_txtScore.setString(intToString(displayedScore));
}

/// BULLETS
/////////////////////////////////////////////////////////////////////
// updateBullets
void Game::State::updateBullets()
{
	size_t bulletsVectorSize = m_bullets.size();
	for(size_t i=0; i<bulletsVectorSize; i++)
	{
		// Out of screen
		if(m_bullets[i].position().x < 0.f || m_bullets[i].position().x > m_orbisMainWindow->getSize().x)
			m_bullets.erase(m_bullets.begin()+i); // Out of screen (X)
		else if(m_bullets[i].position().y < 0.f || m_bullets[i].position().y > m_orbisMainWindow->getSize().y)
			m_bullets.erase(m_bullets.begin()+i); // Out of screen (Y)

		// Update position
		m_bullets[i].setPosition(m_bullets[i].position().x+8*std::cos(m_bullets[i].angle()*PI/180),
								 m_bullets[i].position().y+8*std::sin(m_bullets[i].angle()*PI/180));

		bulletsVectorSize = m_bullets.size();
	}
}


/////////////////////////////////////////////////////////////////////
// drawBullets
void Game::State::drawBullets()
{
	for(size_t i=0; i<m_bullets.size(); i++)
	{
		g_spMainGameBullet.setPosition(m_bullets[i].position());
		m_orbisMainWindow->draw(g_spMainGameBullet);
	}
}


/// INVADERS
/////////////////////////////////////////////////////////////////////
// createInvader
void Game::State::createInvader(float speed, int score)
{
	std::srand(m_gameTimeElapsed.asMilliseconds());
	float angleSpawn;

	sf::Vector2f position = g_spMainGameDisc_1.getPosition();
	if(m_invaders.size() == 0)
	{
		angleSpawn = rand()%360;
		position += sf::Vector2f(700*std::cos(angleSpawn*PI/180),
								 700*std::sin(angleSpawn*PI/180));
		m_invaders.push_back(Invader(m_gameTimeElapsed.asMilliseconds(), angleSpawn, position, speed, rand()%360, score));
	}
	else
	{
		angleSpawn = m_invaders.back().angle()-70;
		angleSpawn += rand()%140;
		position += sf::Vector2f(700*std::cos(angleSpawn*PI/180),
								 700*std::sin(angleSpawn*PI/180));
		m_invaders.push_back(Invader(m_gameTimeElapsed.asMilliseconds(), angleSpawn, position, speed, rand()%360, score));
	}
}


/////////////////////////////////////////////////////////////////////
// spawnInvaders
void Game::State::spawnInvaders()
{
	bool spawnRulesMatch = false;
	for(size_t i=0; i<m_spawnRules.size(); i++)
	{
		if(m_gameTimeElapsed.asMilliseconds() < m_spawnRules[i].timeLimit())
		{
			if(m_invaders.size() == 0)
				createInvader(m_spawnRules[i].invaderSpeed(), m_spawnRules[i].invaderScore());
			else if(m_invaders.size() < m_spawnRules[i].spawnLimit() &&
					(m_gameTimeElapsed.asMilliseconds()-m_invaders.back().time()) >= m_spawnRules[i].spawnInterval())
				createInvader(m_spawnRules[i].invaderSpeed(), m_spawnRules[i].invaderScore());

			spawnRulesMatch = true;
			break;
		}
	}

	if(!spawnRulesMatch)
	{
		if(m_invaders.size() == 0)
			createInvader(m_spawnRules.back().invaderSpeed(), m_spawnRules.back().invaderScore());
		else if(m_invaders.size() < m_spawnRules.back().spawnLimit() &&
				(m_gameTimeElapsed.asMilliseconds()-m_invaders.back().time()) >= m_spawnRules.back().spawnInterval())
			createInvader(m_spawnRules.back().invaderSpeed(), m_spawnRules.back().invaderScore());
	}
}


/////////////////////////////////////////////////////////////////////
// updateInvaders
void Game::State::updateInvaders()
{
	sf::Vector2f position;
	for(size_t i=0; i<m_invaders.size(); i++)
	{
		position = m_invaders[i].position();
		position -= sf::Vector2f(m_invaders[i].speed()*std::cos(m_invaders[i].angle()*PI/180),
								 m_invaders[i].speed()*std::sin(m_invaders[i].angle()*PI/180));
		m_invaders[i].setPosition(position);
		m_invaders[i].setRotation(m_invaders[i].rotation()+2.5f);
	}
}


/////////////////////////////////////////////////////////////////////
// drawInvaders
void Game::State::drawInvaders()
{
	for(size_t i=0; i<m_invaders.size(); i++)
	{
		g_spMainGameInvader.setPosition(m_invaders[i].position());
		g_spMainGameInvader.setRotation(m_invaders[i].rotation());
		m_orbisMainWindow->draw(g_spMainGameInvader);
	}
}


/// COLLISION
/////////////////////////////////////////////////////////////////////
// collisionSolver
void Game::State::collisionSolver()
{
	// Test de collision balles // envahisseurs
	if(m_bullets.size() >= 1 && m_invaders.size() >= 1)
	{
		for(int b=m_bullets.size()-1; b>=0; b--)
		{
			for(int i=m_invaders.size()-1; i>=0; i--)
			{
				float collide = (m_bullets[b].position().x-m_invaders[i].position().x)*(m_bullets[b].position().x-m_invaders[i].position().x);
				collide += (m_bullets[b].position().y-m_invaders[i].position().y)*(m_bullets[b].position().y-m_invaders[i].position().y);
				if(!(collide > (1.5+ 12.5)*(1.5+12.5)))
				{
					// Collision détecté
					m_gameStats.score += m_invaders[i].score();
					m_bullets.erase(m_bullets.begin()+b);
					m_invaders.erase(m_invaders.begin()+i);
				}
			}
		}
	}

	// Test de collision envahisseurs // orbis
	for(size_t i=0; i<m_invaders.size(); i++)
	{
		float collide = (g_spMainGameDisc_1.getPosition().x-m_invaders[i].position().x)*(g_spMainGameDisc_1.getPosition().x-m_invaders[i].position().x);
		collide += (g_spMainGameDisc_1.getPosition().y-m_invaders[i].position().y)*(g_spMainGameDisc_1.getPosition().y-m_invaders[i].position().y);
		if(!(collide > (50.5+12.5)*(50.5+12.5)))
		{
			m_gameOver = true;
			break;
		}
	}
}
