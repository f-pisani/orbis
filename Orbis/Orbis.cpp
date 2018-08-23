#include "Orbis.hpp"

int stringToInt(std::string str)
{
	int tmp;
	std::istringstream iss(str);
	iss >> tmp;
	return tmp;
}


std::string intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}


Orbis::Orbis() : sf::RenderWindow(sf::VideoMode(700, 700), "Orbis", sf::Style::Close, sf::ContextSettings(0, 0, 8, 2, 0)),
    m_windowFocus(true),
    m_gameState(new st4code::StateStack)
{
    sf::RenderWindow::setFramerateLimit(60);

    m_gameState->push(new Menu::State(m_gameState.get(), this));
}


Orbis::~Orbis()
{
}




///=====================================================================
/// PUBLIC
///=====================================================================
/////////////////////////////////////////////////////////////////////
// show
void Orbis::show()
{
    while(sf::RenderWindow::isOpen())
    {
        Orbis::events();
		if(!m_gameState->empty())
		{
			m_gameState->exec();
			while(!m_windowFocus){Orbis::events();}
		}
		else
			break;
    }
}




///=====================================================================
/// PRIVATE
///=====================================================================
/////////////////////////////////////////////////////////////////////
// events
void Orbis::events()
{
    sf::Event event;
    while(sf::RenderWindow::pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            sf::RenderWindow::close();

        if(event.type == sf::Event::GainedFocus)
            m_windowFocus = true;

        if(event.type == sf::Event::LostFocus)
            m_windowFocus = false;
    }
}
