#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Graphics.hpp>
#include <map>

namespace st4code
{
    class Mouse
    {
        public:
            static bool isButtonPressed(sf::Mouse::Button b);
            static bool isButtonReleased(sf::Mouse::Button b);
            static sf::Vector2i getPosition();
            static sf::Vector2i getPosition(const sf::Window &relativeTo);

        private:
            static std::map<sf::Mouse::Button, bool> m_mousemap;
    };
}


#endif // MOUSE_HPP
