#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"

namespace egl
{
    class DrawableFactory
    {
    public:
        static EgDrawable *GetHexagon(sf::Vector2f &pos);
    };
}
