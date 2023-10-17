#include "drawablefactory.hpp"

namespace egl
{
    EgDrawable *DrawableFactory::GetTriangle(Transform *transform)
    {
        auto triangle = sf::VertexArray(sf::Triangles, 3);

        triangle[0].position = sf::Vector2f(-50.f, -50.f);
        triangle[1].position = sf::Vector2f(50.f, -50.f);
        triangle[2].position = sf::Vector2f(50.f, 50.f);

        triangle[0].color = sf::Color::Red;
        triangle[1].color = sf::Color::Blue;
        triangle[2].color = sf::Color::Green;
        return new EgDrawable(transform, triangle);
    }

    EgDrawable *DrawableFactory::GetHexagon(Transform *transform)
    {
        auto hexagon = sf::VertexArray(sf::Triangles, 3);
        auto width = transform->GetScale();
        float sqrt3div2 = 0.86602540378f;

        // https://stackoverflow.com/questions/71816702/coordinates-of-dot-on-an-hexagon-path
        //  ( 1,    0   )
        //  ( 0.5,  √3/2)
        //  (-0.5,  √3/2)
        //  (-1,    0   )
        //  (-0.5, -√3/2)
        //  ( 0.5, -√3/2)
        hexagon[0].position = sf::Vector2f(width, 0);
        hexagon[1].position = sf::Vector2f(width * .5f, width * sqrt3div2);
        hexagon[2].position = sf::Vector2f(width * -.5f, width * sqrt3div2);
        hexagon[3].position = sf::Vector2f(width * -1, 0);
        hexagon[4].position = sf::Vector2f(width * -.5f, width * sqrt3div2 * -1);
        hexagon[5].position = sf::Vector2f(width * .5f, width * sqrt3div2 * -1);

        hexagon[0].color = sf::Color::Red;
        hexagon[1].color = sf::Color::Blue;
        hexagon[2].color = sf::Color::Red;
        hexagon[3].color = sf::Color::Blue;
        hexagon[4].color = sf::Color::Red;
        hexagon[5].color = sf::Color::Blue;
        return new EgDrawable(transform, hexagon);
    }
}