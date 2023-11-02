#include "drawablefactory.hpp"

namespace egl
{
    EgDrawable *DrawableFactory::GetHexagon(sf::Vector2f &pos, float radius)
    {
        auto hexagon = new sf::VertexArray(sf::TriangleFan, 8);
        float sqrt3div2 = 0.86602540378f;

        // https://stackoverflow.com/questions/71816702/coordinates-of-dot-on-an-hexagon-path
        //  ( 1,    0   )
        //  ( 0.5,  √3/2)
        //  (-0.5,  √3/2)
        //  (-1,    0   )
        //  (-0.5, -√3/2)
        //  ( 0.5, -√3/2)
        (*hexagon)[0].position = sf::Vector2f(0, 0);
        (*hexagon)[1].position = sf::Vector2f(0, radius);
        (*hexagon)[2].position = sf::Vector2f(radius * sqrt3div2, radius * .5f);
        (*hexagon)[3].position = sf::Vector2f(radius * sqrt3div2, radius * -.5f);
        (*hexagon)[4].position = sf::Vector2f(0, radius * -1);
        (*hexagon)[5].position = sf::Vector2f(radius * sqrt3div2 * -1, radius * -.5f);
        (*hexagon)[6].position = sf::Vector2f(radius * sqrt3div2 * -1, radius * .5f);
        (*hexagon)[7].position = sf::Vector2f(0, radius);

        auto texCenter = sf::Vector2f(60.f, 70.f);
        auto texRadius = 68.f;
        (*hexagon)[0].texCoords = texCenter + sf::Vector2f(0, 0);
        (*hexagon)[1].texCoords = texCenter + sf::Vector2f(0, texRadius);
        (*hexagon)[2].texCoords = texCenter + sf::Vector2f(texRadius * sqrt3div2, texRadius * .5f);
        (*hexagon)[3].texCoords = texCenter + sf::Vector2f(texRadius * sqrt3div2, texRadius * -.5f);
        (*hexagon)[4].texCoords = texCenter + sf::Vector2f(0, texRadius * -1);
        (*hexagon)[5].texCoords = texCenter + sf::Vector2f(texRadius * sqrt3div2 * -1, texRadius * -.5f);
        (*hexagon)[6].texCoords = texCenter + sf::Vector2f(texRadius * sqrt3div2 * -1, texRadius * .5f);
        (*hexagon)[7].texCoords = texCenter + sf::Vector2f(0, texRadius);

        auto res = new EgDrawable(hexagon);
        res->setPosition(pos);
        return res;
    }

    EgDrawable *DrawableFactory::GetCircle(sf::Vector2f &pos, float radius)
    {
        int resolution = 30;
        auto circle = new sf::VertexArray(sf::TriangleFan, resolution + 2);
        (*circle)[0].position = sf::Vector2f(0.f, 0.f);

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

    EgDrawable *DrawableFactory::GetTriangle(sf::Vector2f size)
    {
        auto triangle = new sf::VertexArray(sf::Triangles, 3);

        (*triangle)[0].position = sf::Vector2f(0, size.y / 2);
        (*triangle)[1].position = sf::Vector2f(size.x / 2, -size.y / 2);
        (*triangle)[2].position = sf::Vector2f(-size.x / 2, -size.y / 2);

        auto res = new EgDrawable(triangle);

        return res;
    }

    EgDrawable *DrawableFactory::GetRectangle(sf::Vector2f size)
    {
        auto boxes = new sf::VertexArray(sf::Triangles, 6);
        auto width = size.x;
        auto height = size.y;
        (*boxes)[0].position = sf::Vector2f(width / -2, height / -2);
        (*boxes)[1].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[2].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[3].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[4].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[5].position = sf::Vector2f(width / 2, height / 2);

        auto texSize = 16.f;
        (*boxes)[0].texCoords = sf::Vector2f(0, 0);
        (*boxes)[1].texCoords = sf::Vector2f(texSize, 0);
        (*boxes)[2].texCoords = sf::Vector2f(0, texSize);
        (*boxes)[3].texCoords = sf::Vector2f(texSize, 0);
        (*boxes)[4].texCoords = sf::Vector2f(0, texSize);
        (*boxes)[5].texCoords = sf::Vector2f(texSize, texSize);
        auto res = new EgDrawable(boxes);

        return res;
    }

    sf::VertexArray *DrawableFactory::GetHealthBar(float width, float height)
    {
        auto boxes = new sf::VertexArray(sf::Triangles, 12);

        (*boxes)[0].position = sf::Vector2f(width / -2, height / -2);
        (*boxes)[1].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[2].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[3].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[4].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[5].position = sf::Vector2f(width / 2, height / 2);

        (*boxes)[6].position = sf::Vector2f(width / -2, height / -2);
        (*boxes)[7].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[8].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[9].position = sf::Vector2f(width / 2, height / -2);
        (*boxes)[10].position = sf::Vector2f(width / -2, height / 2);
        (*boxes)[11].position = sf::Vector2f(width / 2, height / 2);

        (*boxes)[0].color = sf::Color::Green;
        (*boxes)[1].color = sf::Color::Green;
        (*boxes)[2].color = sf::Color::Green;
        (*boxes)[3].color = sf::Color::Green;
        (*boxes)[4].color = sf::Color::Green;
        (*boxes)[5].color = sf::Color::Green;

        (*boxes)[6].color = sf::Color::Transparent;
        (*boxes)[7].color = sf::Color::Transparent;
        (*boxes)[8].color = sf::Color::Transparent;
        (*boxes)[9].color = sf::Color::Transparent;
        (*boxes)[10].color = sf::Color::Transparent;
        (*boxes)[11].color = sf::Color::Transparent;

        return boxes;
    }
}