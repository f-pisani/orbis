#include "Keyboard.hpp"

namespace st4code
{
    std::map<sf::Keyboard::Key, bool> Keyboard::m_keymap;
    ///=====================================================================
    /// PUBLIC
    ///=====================================================================
    /////////////////////////////////////////////////////////////////////
    // isKeyPressed
    bool Keyboard::isKeyPressed(sf::Keyboard::Key k)
    {
        return sf::Keyboard::isKeyPressed(k);
    }




    /////////////////////////////////////////////////////////////////////
    // isKeyReleased
    bool Keyboard::isKeyReleased(sf::Keyboard::Key k)
    {
        if(m_keymap.count(k) == 1)
        {
            if(m_keymap[k] == true)
            {
                if(!isKeyPressed(k))
                {
                    m_keymap[k] = false;
                    return true;
                }
                else
                    return false;
            }
            else
            {
                if(isKeyPressed(k))
                    m_keymap[k] = true;

                return false;
            }
        }
        else
        {
            if(isKeyPressed(k))
                m_keymap.insert(std::make_pair(k, true));
            else
                m_keymap.insert(std::make_pair(k, false));

            return false;
        }
    }
}
