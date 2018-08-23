#include "Record.hpp"

Record::State::State(st4code::StateStack* stateStack, Orbis* orbis) :
	GraphicsState::GraphicsState(stateStack), m_orbisMainWindow(orbis),
	g_ft(), g_txRecordOrbisTypo(), g_spRecordOrbisTypo(),
	g_txtScore(), g_txtMainMenu(), m_selectedMenu(eSelectMenu::MainMenu)
{
	// sf::Font
		g_ft.loadFromFile("data/Neuropol.ttf");
	// sf::Texture
		// Orbis Typo
		g_txRecordOrbisTypo.loadFromFile("data/MainMenuOrbisTypo.png");
	// sf::Sprite
		// Orbis Typo
		g_spRecordOrbisTypo.setTexture(g_txRecordOrbisTypo);
		g_spRecordOrbisTypo.setPosition(m_orbisMainWindow->getSize().x/2-g_spRecordOrbisTypo.getGlobalBounds().width/2,
										  10.f);
	// sf::Text
		// Current score
		g_txtScore.setString(intToString(getScoreMax()));
		g_txtScore.setCharacterSize(108);
		g_txtScore.setFont(g_ft);
		g_txtScore.setPosition(m_orbisMainWindow->getSize().x/2-g_txtScore.getGlobalBounds().width/2,
							   m_orbisMainWindow->getSize().y/2-g_txtScore.getGlobalBounds().height/2);
		// Back to main menu
		g_txtMainMenu.setString("Back to main menu");
		g_txtMainMenu.setCharacterSize(28);
		g_txtMainMenu.setFont(g_ft);
		g_txtMainMenu.setPosition(m_orbisMainWindow->getSize().x/2-g_txtMainMenu.getGlobalBounds().width/2,
								  m_orbisMainWindow->getSize().y-g_txtMainMenu.getGlobalBounds().height-25.f);
}


Record::State::~State()
{
}




///=====================================================================
/// PROTECTED
///=====================================================================
/////////////////////////////////////////////////////////////////////
// preUpdate
void Record::State::preUpdate()
{
	updateTxtFade();
}


/////////////////////////////////////////////////////////////////////
// update
void Record::State::update()
{
	m_orbisMainWindow->clear(sf::Color(10, 15, 40));
		m_orbisMainWindow->draw(g_spRecordOrbisTypo);
		m_orbisMainWindow->draw(g_txtScore);
		m_orbisMainWindow->draw(g_txtMainMenu);
	m_orbisMainWindow->display();
}


/////////////////////////////////////////////////////////////////////
// postUpdate
void Record::State::postUpdate()
{
	mouseOverEvent();
	if(st4code::Keyboard::isKeyReleased(sf::Keyboard::Escape))
		pStateStack->pop(1);

	if(st4code::Mouse::isButtonReleased(sf::Mouse::Left))
	{
		switch(m_selectedMenu)
		{
			case eSelectMenu::MainMenu: pStateStack->pop(1); break;
			default: ;
		}
	}
}




///=====================================================================
/// PRIVATE
///=====================================================================
/////////////////////////////////////////////////////////////////////
// updateTxtFade
void Record::State::updateTxtFade()
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
}


/////////////////////////////////////////////////////////////////////
// mouseOverEvent
void Record::State::mouseOverEvent()
{
	m_selectedMenu = eSelectMenu::None;

	sf::Vector2i mousePosition = st4code::Mouse::getPosition(*m_orbisMainWindow);
	if((mousePosition.x >= g_txtMainMenu.getGlobalBounds().left && mousePosition.x <= g_txtMainMenu.getGlobalBounds().left+g_txtMainMenu.getGlobalBounds().width) &&
	   (mousePosition.y >= g_txtMainMenu.getGlobalBounds().top && mousePosition.y <= g_txtMainMenu.getGlobalBounds().top+g_txtMainMenu.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::MainMenu;
}


/////////////////////////////////////////////////////////////////////
// getScoreMax
int Record::State::getScoreMax()
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
