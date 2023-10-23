#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "math.h"
#include "drawable.hpp"

namespace egl
{
    class DrawableFactory
    {
    public:
        static EgDrawable *GetHexagon(sf::Vector2f &pos, float radius);
        static EgDrawable *GetCircle(sf::Vector2f &pos);
    };
}
