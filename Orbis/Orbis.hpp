#ifndef ORBIS_HPP
#define ORBIS_HPP

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "../st4code/StateStack.hpp"
#include "Menu.hpp"

int stringToInt(std::string str);
std::string intToString(int number);

class Orbis : public sf::RenderWindow
{
    public:
        Orbis();
        ~Orbis();
        void show();
        inline bool isWindowFocus() { return m_windowFocus; }

    private:
        void events();

        bool m_windowFocus;
        std::unique_ptr<st4code::StateStack> m_gameState;
};

#endif // ORBIS_HPP
