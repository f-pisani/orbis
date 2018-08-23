#include "Mouse.hpp"

namespace st4code
{
    std::map<sf::Mouse::Button, bool> Mouse::m_mousemap;
    ///=====================================================================
    /// PUBLIC
    ///=====================================================================
    /////////////////////////////////////////////////////////////////////
    // isButtonPressed
    bool Mouse::isButtonPressed(sf::Mouse::Button b)
    {
        return sf::Mouse::isButtonPressed(b);
    }




    /////////////////////////////////////////////////////////////////////
    // isButtonReleased
    bool Mouse::isButtonReleased(sf::Mouse::Button b)
    {
        if(m_mousemap.count(b) == 1)
        {
            if(m_mousemap[b] == true)
            {
                if(!isButtonPressed(b))
                {
                    m_mousemap[b] = false;
                    return true;
                }
                else
                    return false;
            }
            else
            {
                if(isButtonPressed(b))
                    m_mousemap[b] = true;

                return false;
            }
        }
        else
        {
            if(isButtonPressed(b))
                m_mousemap.insert(std::make_pair(b, true));
            else
                m_mousemap.insert(std::make_pair(b, false));

            return false;
        }
    }




    /////////////////////////////////////////////////////////////////////
    // getPosition
    sf::Vector2i Mouse::getPosition()
    {
        return sf::Mouse::getPosition();
    }




    /////////////////////////////////////////////////////////////////////
    // getPosition
    sf::Vector2i Mouse::getPosition(const sf::Window &relativeTo)
    {
        return sf::Mouse::getPosition(relativeTo);
    }
}
