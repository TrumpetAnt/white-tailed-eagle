#pragma once

#include <SFML/System/Vector3.hpp>

namespace egl
{
    class Transform
    {
    private:
        sf::Vector3f position = sf::Vector3f(0, 0, 0);

    public:
        sf::Vector3f GetPosition()
        {
            return position;
        }

        void SetPosition(sf::Vector3f pos)
        {
            position = pos;
        }
    };
}