#include "drawable.hpp"

namespace egl
{
    sf::VertexArray Drawable::GetVertexArray()
    {
        auto pos = transform->GetPosition();
        auto offset_x = pos.x;
        auto offset_y = pos.y;
        sf::VertexArray triangle(sf::Triangles, 3);

        // define the position of the triangle's points
        triangle[0].position = sf::Vector2f(offset_x + 10.f, offset_y + 10.f);
        triangle[1].position = sf::Vector2f(offset_x + 100.f, offset_y + 10.f);
        triangle[2].position = sf::Vector2f(offset_x + 100.f, offset_y + 100.f);

        // define the color of the triangle's points
        triangle[0].color = sf::Color::Red;
        triangle[1].color = sf::Color::Blue;
        triangle[2].color = sf::Color::Green;
        return triangle;
    }
}