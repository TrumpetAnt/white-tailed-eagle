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

        // std::cout << "Vertex at (" << (*hexagon)[0].position.x << "," << (*hexagon)[0].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[1].position.x << "," << (*hexagon)[1].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[2].position.x << "," << (*hexagon)[2].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[3].position.x << "," << (*hexagon)[3].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[4].position.x << "," << (*hexagon)[4].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[5].position.x << "," << (*hexagon)[5].position.y << ")" << std::endl;
        // std::cout << "Vertex at (" << (*hexagon)[6].position.x << "," << (*hexagon)[6].position.y << ")" << std::endl;

        (*hexagon)[0].color = sf::Color::Red;
        (*hexagon)[1].color = sf::Color::Blue;
        (*hexagon)[2].color = sf::Color::Green;
        (*hexagon)[3].color = sf::Color::Red;
        (*hexagon)[4].color = sf::Color::Blue;
        (*hexagon)[5].color = sf::Color::Green;
        (*hexagon)[6].color = sf::Color::Red;
        (*hexagon)[7].color = sf::Color::Blue;
        (*hexagon)[8].color = sf::Color::Green;
        (*hexagon)[9].color = sf::Color::Red;
        auto res = new EgDrawable(hexagon);
        res->setPosition(pos);
        return res;
    }
}