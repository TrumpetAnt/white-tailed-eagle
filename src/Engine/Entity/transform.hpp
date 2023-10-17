#pragma once

#include <SFML/System/Vector3.hpp>

namespace egl
{
    class Transform
    {
    private:
        sf::Vector3f position = sf::Vector3f(0, 0, 0);
        float scale = 1.0f;

    public:
        sf::Vector3f GetPosition()
        {
            return position;
        }

        float GetScale()
        {
            return scale;
        }

        void SetPosition(sf::Vector3f pos)
        {
            position = pos;
        }

        void SetScale(float s)
        {
            scale = s;
        }
    };
}