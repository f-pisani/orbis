#include "GameOver.hpp"

GameOver::State::State(st4code::StateStack* stateStack, Orbis* orbis, GameStats gameStats) :
	GraphicsState::GraphicsState(stateStack), m_orbisMainWindow(orbis), m_gameStats(gameStats),
	g_ft(), g_txGameOverBackground(), g_txGameOverOrbisTypo(),
	g_spGameOverBackground(), g_spGameOverOrbisTypo(),
	g_txtScore(), g_txtScoreMax(), g_txtMainMenu(), g_txtExit(), m_selectedMenu(eSelectMenu::None)
{
	// sf::Font
		g_ft.loadFromFile("data/Neuropol.ttf");
	// sf::Texture
		// Background (the current game screen (when an invader hit the orbis))
		g_txGameOverBackground.loadFromImage(m_orbisMainWindow->capture());
		// Orbis Typo
		g_txGameOverOrbisTypo.loadFromFile("data/MainMenuOrbisTypo.png");
	// sf::Sprite
		// Background
		g_spGameOverBackground.setTexture(g_txGameOverBackground);
		g_spGameOverBackground.setColor(sf::Color(255, 255, 255, 50));
		// Orbis Typo
		g_spGameOverOrbisTypo.setTexture(g_txGameOverOrbisTypo);
		g_spGameOverOrbisTypo.setPosition(m_orbisMainWindow->getSize().x/2-g_spGameOverOrbisTypo.getGlobalBounds().width/2,
										  10.f);
	// sf::Text
		// Current score
		g_txtScore.setString(intToString(m_gameStats.score));
		g_txtScore.setCharacterSize(108);
		g_txtScore.setFont(g_ft);
		g_txtScore.setPosition(m_orbisMainWindow->getSize().x/2-g_txtScore.getGlobalBounds().width/2,
							   m_orbisMainWindow->getSize().y/2-g_txtScore.getGlobalBounds().height/2);

		if(getScoreMax() < m_gameStats.score)
		{
			g_txtScoreMax.setString(intToString(m_gameStats.score));
			g_txtScoreMax.setColor(sf::Color::Blue);
		}
		else
		{
			g_txtScoreMax.setString(intToString(getScoreMax()));
			g_txtScoreMax.setColor(sf::Color::Red);
		}
		// Score max
		g_txtScoreMax.setCharacterSize(46);
		g_txtScoreMax.setFont(g_ft);
		g_txtScoreMax.setPosition(m_orbisMainWindow->getSize().x/2-g_txtScoreMax.getGlobalBounds().width/2,
								  g_txtScore.getPosition().y+g_txtScore.getGlobalBounds().height*2);
		// Back to main menu
		g_txtMainMenu.setString("Back to main menu");
		g_txtMainMenu.setCharacterSize(28);
		g_txtMainMenu.setFont(g_ft);
		g_txtMainMenu.setPosition(m_orbisMainWindow->getSize().x/4-g_txtMainMenu.getGlobalBounds().width/2,
								  m_orbisMainWindow->getSize().y-g_txtMainMenu.getGlobalBounds().height-25.f);
		// Back to desktop
		g_txtExit.setString("Back to desktop");
		g_txtExit.setCharacterSize(28);
		g_txtExit.setFont(g_ft);
		g_txtExit.setPosition(m_orbisMainWindow->getSize().x/4*3-g_txtExit.getGlobalBounds().width/2,
							  m_orbisMainWindow->getSize().y-g_txtExit.getGlobalBounds().height-25.f);
	// Checkout the current score and save it if it's a new record
		if(getScoreMax() < m_gameStats.score)
			saveNewScoreMax();
}


GameOver::State::~State()
{
}




///=====================================================================
/// PROTECTED
///=====================================================================
/////////////////////////////////////////////////////////////////////
// preUpdate
void GameOver::State::preUpdate()
{
	updateTxtFade();
}


/////////////////////////////////////////////////////////////////////
// update
void GameOver::State::update()
{
	m_orbisMainWindow->clear(sf::Color::Black);
		m_orbisMainWindow->draw(g_spGameOverBackground);
		m_orbisMainWindow->draw(g_spGameOverOrbisTypo);
		m_orbisMainWindow->draw(g_txtScore);
		m_orbisMainWindow->draw(g_txtScoreMax);
		m_orbisMainWindow->draw(g_txtMainMenu);
		m_orbisMainWindow->draw(g_txtExit);
	m_orbisMainWindow->display();
}


/////////////////////////////////////////////////////////////////////
// postUpdate
void GameOver::State::postUpdate()
{
	mouseOverEvent();
	if(st4code::Keyboard::isKeyReleased(sf::Keyboard::Escape))
		pStateStack->pop(1);

	if(st4code::Mouse::isButtonReleased(sf::Mouse::Left))
	{
		switch(m_selectedMenu)
		{
			case eSelectMenu::MainMenu: pStateStack->pop(1); break;
			case eSelectMenu::Exit: pStateStack->pop(2); break;
			default: ;
		}
	}
}




///=====================================================================
/// PRIVATE
///=====================================================================
/////////////////////////////////////////////////////////////////////
// updateTxtFade
void GameOver::State::updateTxtFade()
{
	// Back to main menu
	if(m_selectedMenu == eSelectMenu::MainMenu)
	{
		if(g_txtMainMenu.getColor() != sf::Color(255, 255, 255))
			g_txtMainMenu.setColor(sf::Color(g_txtMainMenu.getColor().r+5, g_txtMainMenu.getColor().g+5, g_txtMainMenu.getColor().b+5));
	}
	else
	{
		if(g_txtMainMenu.getColor() != sf::Color(85, 85, 85))
			g_txtMainMenu.setColor(sf::Color(g_txtMainMenu.getColor().r-5, g_txtMainMenu.getColor().g-5, g_txtMainMenu.getColor().b-5));
	}

	// Back to desktop
	if(m_selectedMenu == eSelectMenu::Exit)
	{
		if(g_txtExit.getColor() != sf::Color(255, 255, 255))
			g_txtExit.setColor(sf::Color(g_txtExit.getColor().r+5, g_txtExit.getColor().g+5, g_txtExit.getColor().b+5));
	}
	else
	{
		if(g_txtExit.getColor() != sf::Color(85, 85, 85))
			g_txtExit.setColor(sf::Color(g_txtExit.getColor().r-5, g_txtExit.getColor().g-5, g_txtExit.getColor().b-5));
	}
}


/////////////////////////////////////////////////////////////////////
// mouseOverEvent
void GameOver::State::mouseOverEvent()
{
	m_selectedMenu = eSelectMenu::None;

	sf::Vector2i mousePosition = st4code::Mouse::getPosition(*m_orbisMainWindow);
	if((mousePosition.x >= g_txtMainMenu.getGlobalBounds().left && mousePosition.x <= g_txtMainMenu.getGlobalBounds().left+g_txtMainMenu.getGlobalBounds().width) &&
	   (mousePosition.y >= g_txtMainMenu.getGlobalBounds().top && mousePosition.y <= g_txtMainMenu.getGlobalBounds().top+g_txtMainMenu.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::MainMenu;
	else if((mousePosition.x >= g_txtExit.getGlobalBounds().left && mousePosition.x <= g_txtExit.getGlobalBounds().left+g_txtExit.getGlobalBounds().width) &&
			(mousePosition.y >= g_txtExit.getGlobalBounds().top && mousePosition.y <= g_txtExit.getGlobalBounds().top+g_txtExit.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Exit;
}


/////////////////////////////////////////////////////////////////////
// saveNewScoreMax
void GameOver::State::saveNewScoreMax()
{
	std::fstream file;
	file.open("data/score.bin", std::ios::out | std::ios::trunc | std::ios::binary);
	if(file.is_open())
	{
		file.write(reinterpret_cast<const char*>(&m_gameStats.score), sizeof(int));
		file.close();
	}
}


/////////////////////////////////////////////////////////////////////
// getScoreMax
int GameOver::State::getScoreMax()
{
	int score_max = 0;

	std::fstream file;
	file.open("data/score.bin", std::ios::in | std::ios::binary);
	if(file.is_open())
	{
		file.read(reinterpret_cast<char*>(&score_max), sizeof(int));
		file.close();
	}

	return score_max;
}
