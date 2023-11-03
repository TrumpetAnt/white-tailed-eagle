#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "math.h"
#include "drawable.hpp"

namespace egl
{
    class DrawableFactory
    {
    private:
        static sf::VertexArray *RectangeVertexArray(sf::Vector2f size);
        static void RectangeSetTextCoords(sf::VertexArray *vertexArray, sf::Vector2f textureSize);

    public:
        static EgDrawable *GetHexagon(sf::Vector2f &pos, float radius);
        static EgDrawable *GetCircle(sf::Vector2f &pos, float radius);
        static EgDrawable *GetTriangle(sf::Vector2f size);
        static EgDrawable *GetRectangle(sf::Vector2f size);
        static EgDrawable *GetRectangle(sf::Vector2f size, sf::Vector2f textureSize);
        static sf::VertexArray *GetHealthBar(float width, float height);
    };
}
