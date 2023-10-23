#include "drawablefactory.hpp"

namespace egl
{
    EgDrawable *DrawableFactory::GetHexagon(sf::Vector2f &pos)
    {
        auto hexagon = new sf::VertexArray(sf::TriangleFan, 8);
        auto width = 40;
        float sqrt3div2 = 0.86602540378f;

        // https://stackoverflow.com/questions/71816702/coordinates-of-dot-on-an-hexagon-path
        //  ( 1,    0   )
        //  ( 0.5,  √3/2)
        //  (-0.5,  √3/2)
        //  (-1,    0   )
        //  (-0.5, -√3/2)
        //  ( 0.5, -√3/2)
        (*hexagon)[0].position = sf::Vector2f(0, 0);
        (*hexagon)[1].position = sf::Vector2f(width, 0);
        (*hexagon)[2].position = sf::Vector2f(width * .5f, width * sqrt3div2);
        (*hexagon)[3].position = sf::Vector2f(width * -.5f, width * sqrt3div2);
        (*hexagon)[4].position = sf::Vector2f(width * -1, 0);
        (*hexagon)[5].position = sf::Vector2f(width * -.5f, width * sqrt3div2 * -1);
        (*hexagon)[6].position = sf::Vector2f(width * .5f, width * sqrt3div2 * -1);
        (*hexagon)[7].position = sf::Vector2f(width, 0);

        auto res = new EgDrawable(hexagon);
        res->setPosition(pos);
        return res;
    }

    EgDrawable *DrawableFactory::GetCircle(sf::Vector2f &pos)
    {
        int resolution = 30;
        auto circle = new sf::VertexArray(sf::TriangleFan, resolution + 2);
        (*circle)[0].position = sf::Vector2f(0.f, 0.f);

        float radius = 25.f;
        auto v_count = circle->getVertexCount();
        for (int i = 1; i < v_count; i++)
        {
            auto rad = static_cast<float>(i - 1) / static_cast<float>(v_count - 2) * 2 * M_PI;
            (*circle)[i].position = sf::Vector2f(cos(rad) * radius, sin(rad) * radius);
        }

        auto res = new EgDrawable(circle);
        res->setPosition(pos);
        return res;
    }
}