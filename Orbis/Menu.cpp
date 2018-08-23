#include "Menu.hpp"

Menu::State::State(st4code::StateStack* stateStack, Orbis* orbis) :
    GraphicsState::GraphicsState(stateStack), m_orbisMainWindow(orbis),
    g_ft(), g_txMainMenuOrbisTypo(), g_txMainMenuDisc_1(), g_txMainMenuDisc_2(),
    g_spMainMenuOrbisTypo(), g_spMainMenuDisc_1(), g_spMainMenuDisc_2(),
    g_txtPlay(), g_txtRecord(), g_txtCredit(), g_txtExit(),
    m_selectedMenu(eSelectMenu::Play), m_angleDisc2(270)
{
    // sf::Font
		g_ft.loadFromFile("data/Neuropol.ttf");
    // sf::Texture
		// Orbis typo
		g_txMainMenuOrbisTypo.loadFromFile("data/MainMenuOrbisTypo.png");
		g_txMainMenuOrbisTypo.setSmooth(true);
		// First circle
		g_txMainMenuDisc_1.loadFromFile("data/MainGameDisc_1.png");
		g_txMainMenuDisc_1.setSmooth(true);
		// Second circle
		g_txMainMenuDisc_2.loadFromFile("data/MainGameDisc_2.png");
		g_txMainMenuDisc_2.setSmooth(true);
    // sf::Sprite
		// Orbis typo
		g_spMainMenuOrbisTypo.setTexture(g_txMainMenuOrbisTypo);
		g_spMainMenuOrbisTypo.setPosition(m_orbisMainWindow->getSize().x/2-g_txMainMenuOrbisTypo.getSize().x/2,
										  m_orbisMainWindow->getSize().y/6-g_txMainMenuOrbisTypo.getSize().y/2);
		// First circle
		g_spMainMenuDisc_1.setTexture(g_txMainMenuDisc_1);
		g_spMainMenuDisc_1.setOrigin(g_spMainMenuDisc_1.getLocalBounds().width/2,
									 g_spMainMenuDisc_1.getLocalBounds().height/2);
		g_spMainMenuDisc_1.setPosition(m_orbisMainWindow->getSize().x/2,
									   m_orbisMainWindow->getSize().y/2+125);
		// Second circle
		g_spMainMenuDisc_2.setTexture(g_txMainMenuDisc_2);
		g_spMainMenuDisc_2.setOrigin(g_spMainMenuDisc_2.getLocalBounds().width/2,
									 g_spMainMenuDisc_2.getLocalBounds().height/2);
    // sf::Text
		// Play
		g_txtPlay.setString("Play");
		g_txtPlay.setCharacterSize(46);
		g_txtPlay.setFont(g_ft);
		g_txtPlay.setOrigin(g_txtPlay.getLocalBounds().width/2, g_txtPlay.getLocalBounds().height);
		g_txtPlay.setPosition(g_spMainMenuDisc_1.getPosition().x,
							  g_spMainMenuDisc_1.getPosition().y-g_spMainMenuDisc_1.getLocalBounds().height-6);
		// Record
		g_txtRecord.setString("Record");
		g_txtRecord.setCharacterSize(46);
		g_txtRecord.setFont(g_ft);
		g_txtRecord.setOrigin(g_txtRecord.getLocalBounds().width, g_txtRecord.getLocalBounds().height);
		g_txtRecord.setPosition(g_spMainMenuDisc_1.getPosition().x-g_spMainMenuDisc_1.getLocalBounds().width-6,
								g_spMainMenuDisc_1.getPosition().y);
		// Crédit
		g_txtCredit.setString("Credit");
		g_txtCredit.setCharacterSize(46);
		g_txtCredit.setFont(g_ft);
		g_txtCredit.setOrigin(0, g_txtCredit.getLocalBounds().height);
		g_txtCredit.setPosition(g_spMainMenuDisc_1.getPosition().x+g_spMainMenuDisc_1.getLocalBounds().width+6,
								g_spMainMenuDisc_1.getPosition().y);
		// Exit
		g_txtExit.setString("Exit");
		g_txtExit.setCharacterSize(46);
		g_txtExit.setFont(g_ft);
		g_txtExit.setOrigin(g_txtExit.getLocalBounds().width/2, g_txtExit.getLocalBounds().height);
		g_txtExit.setPosition(g_spMainMenuDisc_1.getPosition().x,
							  g_spMainMenuDisc_1.getPosition().y+g_spMainMenuDisc_1.getLocalBounds().height+6);
}


Menu::State::~State()
{
}




///=====================================================================
/// PROTECTED
///=====================================================================
/////////////////////////////////////////////////////////////////////
// preUpdate
void Menu::State::preUpdate()
{
	updateDiscAnimation();
	updateTxtFade();
}


/////////////////////////////////////////////////////////////////////
// update
void Menu::State::update()
{
    m_orbisMainWindow->clear(sf::Color(10, 15, 40));
        m_orbisMainWindow->draw(g_spMainMenuOrbisTypo);
        m_orbisMainWindow->draw(g_spMainMenuDisc_1);
        m_orbisMainWindow->draw(g_spMainMenuDisc_2);
        m_orbisMainWindow->draw(g_txtPlay);
		m_orbisMainWindow->draw(g_txtRecord);
        m_orbisMainWindow->draw(g_txtCredit);
        m_orbisMainWindow->draw(g_txtExit);
    m_orbisMainWindow->display();
}


/////////////////////////////////////////////////////////////////////
// postUpdate
void Menu::State::postUpdate()
{
	mouseOverEvent();
	if(st4code::Keyboard::isKeyReleased(sf::Keyboard::Escape))
		pStateStack->pop(1);

    if(st4code::Mouse::isButtonReleased(sf::Mouse::Left))
    {
        switch(m_selectedMenu)
        {
            case eSelectMenu::Play: pStateStack->push(new Game::State(pStateStack.get(), m_orbisMainWindow)); break;
			case eSelectMenu::Record: pStateStack->push(new Record::State(pStateStack.get(), m_orbisMainWindow)); break;
			case eSelectMenu::Credit: ; break;
            case eSelectMenu::Exit: pStateStack->clear(); break;
            default: ;
        }
    }
}




///=====================================================================
/// PRIVATE
///=====================================================================
/////////////////////////////////////////////////////////////////////
// mouseOverEvent
void Menu::State::mouseOverEvent()
{
	sf::Vector2i mousePosition = st4code::Mouse::getPosition(*m_orbisMainWindow);
	if((mousePosition.x >= g_txtPlay.getGlobalBounds().left && mousePosition.x <= g_txtPlay.getGlobalBounds().left+g_txtPlay.getGlobalBounds().width) &&
	   (mousePosition.y >= g_txtPlay.getGlobalBounds().top && mousePosition.y <= g_txtPlay.getGlobalBounds().top+g_txtPlay.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Play;
	else if((mousePosition.x >= g_txtExit.getGlobalBounds().left && mousePosition.x <= g_txtExit.getGlobalBounds().left+g_txtExit.getGlobalBounds().width) &&
			(mousePosition.y >= g_txtExit.getGlobalBounds().top && mousePosition.y <= g_txtExit.getGlobalBounds().top+g_txtExit.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Exit;
	else if((mousePosition.x >= g_txtRecord.getGlobalBounds().left && mousePosition.x <= g_txtRecord.getGlobalBounds().left+g_txtRecord.getGlobalBounds().width) &&
			(mousePosition.y >= g_txtRecord.getGlobalBounds().top && mousePosition.y <= g_txtRecord.getGlobalBounds().top+g_txtRecord.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Record;
	else if((mousePosition.x >= g_txtCredit.getGlobalBounds().left && mousePosition.x <= g_txtCredit.getGlobalBounds().left+g_txtCredit.getGlobalBounds().width) &&
			(mousePosition.y >= g_txtCredit.getGlobalBounds().top && mousePosition.y <= g_txtCredit.getGlobalBounds().top+g_txtCredit.getGlobalBounds().height))
		m_selectedMenu = eSelectMenu::Credit;
}


/////////////////////////////////////////////////////////////////////
// updateDiscAnimation
void Menu::State::updateDiscAnimation()
{
	g_spMainMenuDisc_1.rotate(0.5f);
	g_spMainMenuDisc_2.rotate(-0.5f);

	int target_angle = 270;
	switch(m_selectedMenu)
	{
		case eSelectMenu::Play:
			target_angle = atan2(g_txtPlay.getPosition().y - g_spMainMenuDisc_1.getPosition().y,
								 g_txtPlay.getPosition().x - g_spMainMenuDisc_1.getPosition().x)*180/PI;
		break;

		case eSelectMenu::Record:
			target_angle = atan2(g_txtRecord.getPosition().y - g_spMainMenuDisc_1.getPosition().y,
								 g_txtRecord.getPosition().x - g_spMainMenuDisc_1.getPosition().x)*180/PI;
		break;

		case eSelectMenu::Credit:
			target_angle = atan2(g_txtCredit.getPosition().y - g_spMainMenuDisc_1.getPosition().y,
								 g_txtCredit.getPosition().x - g_spMainMenuDisc_1.getPosition().x)*180/PI;
		break;

		case eSelectMenu::Exit:
			target_angle = atan2(g_txtExit.getPosition().y - g_spMainMenuDisc_1.getPosition().y,
								 g_txtExit.getPosition().x - g_spMainMenuDisc_1.getPosition().x)*180/PI;
		break;

		default: ;
	}

	if(target_angle < 0)
		target_angle += 360;

	if(target_angle < m_angleDisc2)
	{
		if(m_angleDisc2-target_angle <= 180)
			m_angleDisc2 = (m_angleDisc2-2)%360;
		else
			m_angleDisc2 = (m_angleDisc2+2)%360;
	}
	else if(target_angle > m_angleDisc2)
	{
		if(target_angle-m_angleDisc2 <= 180)
			m_angleDisc2 = (m_angleDisc2+2)%360;
		else
		{
			if(m_angleDisc2-2 < 0)
				m_angleDisc2 = 360-2;
			else
				m_angleDisc2 = (m_angleDisc2-2)%360;
		}
	}

	g_spMainMenuDisc_2.setPosition(g_spMainMenuDisc_1.getPosition().x+70*std::cos(m_angleDisc2*PI/180),
								   g_spMainMenuDisc_1.getPosition().y+70*std::sin(m_angleDisc2*PI/180));
}


/////////////////////////////////////////////////////////////////////
// updateTxtFade
void Menu::State::updateTxtFade()
{
	// Play
	if(m_selectedMenu == eSelectMenu::Play)
	{
		if(g_txtPlay.getColor() != sf::Color(255, 255, 255))
			g_txtPlay.setColor(sf::Color(g_txtPlay.getColor().r+5, g_txtPlay.getColor().g+5, g_txtPlay.getColor().b+5));
	}
	else
	{
		if(g_txtPlay.getColor() != sf::Color(85, 85, 85))
			g_txtPlay.setColor(sf::Color(g_txtPlay.getColor().r-5, g_txtPlay.getColor().g-5, g_txtPlay.getColor().b-5));
	}

	// Record
	if(m_selectedMenu == eSelectMenu::Record)
	{
		if(g_txtRecord.getColor() != sf::Color(255, 255, 255))
			g_txtRecord.setColor(sf::Color(g_txtRecord.getColor().r+5, g_txtRecord.getColor().g+5, g_txtRecord.getColor().b+5));
	}
	else
	{
		if(g_txtRecord.getColor() != sf::Color(85, 85, 85))
			g_txtRecord.setColor(sf::Color(g_txtRecord.getColor().r-5, g_txtRecord.getColor().g-5, g_txtRecord.getColor().b-5));
	}

	// Credit
	if(m_selectedMenu == eSelectMenu::Credit)
	{
		if(g_txtCredit.getColor() != sf::Color(255, 255, 255))
			g_txtCredit.setColor(sf::Color(g_txtCredit.getColor().r+5, g_txtCredit.getColor().g+5, g_txtCredit.getColor().b+5));
	}
	else
	{
		if(g_txtCredit.getColor() != sf::Color(85, 85, 85))
			g_txtCredit.setColor(sf::Color(g_txtCredit.getColor().r-5, g_txtCredit.getColor().g-5, g_txtCredit.getColor().b-5));
	}

	// Exit
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
