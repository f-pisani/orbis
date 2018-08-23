#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/Graphics.hpp>
#include <map>

namespace st4code
{
    class Keyboard
    {
        public:
            static bool isKeyPressed(sf::Keyboard::Key k);
            static bool isKeyReleased(sf::Keyboard::Key k);

        private:
            static std::map<sf::Keyboard::Key, bool> m_keymap;
    };
}


#endif // KEYBOARD_HPP
