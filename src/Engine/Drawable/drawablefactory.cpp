#include "drawablefactory.hpp"

namespace egl
{
    EgDrawable *DrawableFactory::GetHexagon(sf::Vector2f &pos)
    {
        auto hexagon = new sf::VertexArray(sf::TriangleStrip, 10);
        auto width = 40;
        float sqrt3div2 = 0.86602540378f;

        // https://stackoverflow.com/questions/71816702/coordinates-of-dot-on-an-hexagon-path
        //  ( 1,    0   )
        //  ( 0.5,  √3/2)
        //  (-0.5,  √3/2)
        //  (-1,    0   )
        //  (-0.5, -√3/2)
        //  ( 0.5, -√3/2)
        (*hexagon)[0].position = sf::Vector2f(width, 0);
        (*hexagon)[1].position = sf::Vector2f(width * .5f, width * sqrt3div2);
        (*hexagon)[2].position = sf::Vector2f(0, 0);
        (*hexagon)[3].position = sf::Vector2f(width * -.5f, width * sqrt3div2);
        (*hexagon)[4].position = sf::Vector2f(width * -1, 0);
        (*hexagon)[5].position = sf::Vector2f(0, 0);
        (*hexagon)[6].position = sf::Vector2f(width * -.5f, width * sqrt3div2 * -1);
        (*hexagon)[7].position = sf::Vector2f(width * .5f, width * sqrt3div2 * -1);
        (*hexagon)[8].position = sf::Vector2f(0, 0);
        (*hexagon)[9].position = sf::Vector2f(width, 0);

        auto res = new EgDrawable(hexagon);
        res->setPosition(pos);
        return res;
    }
}