#pragma once

#include "SFML/Graphics.hpp"
#include "math.h"
#include <iostream>

namespace egl
{
    namespace vecop
    {
        float Magnitude(sf::Vector2f vec);
        float AngleBetweenVectors(sf::Vector2f a, sf::Vector2f b);
        sf::Vector2f InBetween(sf::Vector2f a, sf::Vector2f b);
        void PrintVector(sf::Vector2f a);
    }
}
