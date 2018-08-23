#include "Pause.hpp"

Pause::State::State(st4code::StateStack* stateStack, Orbis* orbis) :
	GraphicsState::GraphicsState(stateStack), m_orbisMainWindow(orbis),
	g_ft(), g_txPauseGameBackground(), g_txPauseGameOrbisTypo(),
	g_spPauseGameBackground(), g_spPauseGameOrbisTypo(),
	g_txtResume(), g_txtExit(), m_selectedMenu(eSelectMenu::None)
{
	// sf::Font
		g_ft.loadFromFile("data/Neuropol.ttf");
	// sf::Texture
		// Background (the current game screen)
		g_txPauseGameBackground.loadFromImage(m_orbisMainWindow->capture());
		// Orbis Typo
		g_txPauseGameOrbisTypo.loadFromFile("data/MainMenuOrbisTypo.png");
	// sf::Sprite
		// Background
		g_spPauseGameBackground.setTexture(g_txPauseGameBackground);
		g_spPauseGameBackground.setColor(sf::Color(255, 255, 255, 50));
		// Orbis Typo
		g_spPauseGameOrbisTypo.setTexture(g_txPauseGameOrbisTypo);
		g_spPauseGameOrbisTypo.setPosition(m_orbisMainWindow->getSize().x/2-g_spPauseGameOrbisTypo.getGlobalBounds().width/2,
										   10.f);
	// sf::Text
		// Resume
		g_txtResume.setString("Resume");
		g_txtResume.setCharacterSize(46);
		g_txtResume.setFont(g_ft);
		g_txtResume.setPosition(m_orbisMainWindow->getSize().x/2-g_txtResume.getGlobalBounds().width/2,
								m_orbisMainWindow->getSize().y/2-g_txtResume.getGlobalBounds().height/2);
		// Back to main menu
		g_txtExit.setString("Back to main menu");
		g_txtExit.setCharacterSize(46);
		g_txtExit.setFont(g_ft);
		g_txtExit.setPosition(m_orbisMainWindow->getSize().x/2-g_txtExit.getGlobalBounds().width/2,
							  g_txtResume.getPosition().y+g_txtResume.getGlobalBounds().height+20.f);
}


Pause::State::~State()
{
}




///=====================================================================
/// PROTECTED
///=====================================================================
/////////////////////////////////////////////////////////////////////
// preUpdate
void Pause::State::preUpdate()
{
	updateTxtFade();
}


/////////////////////////////////////////////////////////////////////
// update
void Pause::State::update()
{
	m_orbisMainWindow->clear(sf::Color::Black);
		m_orbisMainWindow->draw(g_spPauseGameBackground);
		m_orbisMainWindow->draw(g_spPauseGameOrbisTypo);
		m_orbisMainWindow->draw(g_txtResume);
		m_orbisMainWindow->draw(g_txtExit);
	m_orbisMainWindow->display();
}


/////////////////////////////////////////////////////////////////////
// postUpdate
void Pause::State::postUpdate()
{
	mouseOverEvent();
	if(st4code::Keyboard::isKeyReleased(sf::Keyboard::Escape))
		pStateStack->pop();

	if(st4code::Mouse::isButtonReleased(sf::Mouse::Left))
	{
		switch(m_selectedMenu)
		{
			case eSelectMenu::Resume: pStateStack->pop(); break;
			case eSelectMenu::Exit: pStateStack->pop(2); break;
			default: ;
		}
	}
}




///=====================================================================
/// PRIVATE
///=====================================================================
/////////////////////////////////////////////////////////////////////
// mouseOverEvent
void Pause::State::mouseOverEvent()
{
	m_selectedMenu = eSelectMenu::None;

	sf::Vector2i mousePosition = st4code::Mouse::getPosition(*m_orbisMainWindow);
	if((mousePosition.x >= g_txtResume.getGlobalBounds().left && mousePosition.x <= g_txtResume.getGlobalBounds().left+g_txtResume.getGlobalBounds().width) &&
	   (mousePosition.y >= g_txtResume.getGlobalBounds().top && mousePosition.y <= g_txtResume.getGlobalBounds().top+g_txtResume.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Resume;
	else if((mousePosition.x >= g_txtExit.getGlobalBounds().left && mousePosition.x <= g_txtExit.getGlobalBounds().left+g_txtExit.getGlobalBounds().width) &&
			(mousePosition.y >= g_txtExit.getGlobalBounds().top && mousePosition.y <= g_txtExit.getGlobalBounds().top+g_txtExit.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Exit;
}


/////////////////////////////////////////////////////////////////////
// updateTxtFade
void Pause::State::updateTxtFade()
{
	// Resume
	if(m_selectedMenu == eSelectMenu::Resume)
	{
		if(g_txtResume.getColor() != sf::Color(255, 255, 255))
			g_txtResume.setColor(sf::Color(g_txtResume.getColor().r+5, g_txtResume.getColor().g+5, g_txtResume.getColor().b+5));
	}
	else
	{
		if(g_txtResume.getColor() != sf::Color(85, 85, 85))
			g_txtResume.setColor(sf::Color(g_txtResume.getColor().r-5, g_txtResume.getColor().g-5, g_txtResume.getColor().b-5));
	}

	// Back to main menu
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
