#include "drawable.hpp"

namespace egl
{
    void EgDrawable::SetTexture(sf::Texture *t)
    {
        texture = t;
    }

    void EgDrawable::SetColor(sf::Color c)
    {
        if (c == color)
        {
            return;
        }
        color = c;
        auto v_count = vertexArray->getVertexCount();
        for (int i = 0; i < v_count; i++)
        {
            (*vertexArray)[i].color = color;
        };
    }

    void EgDrawable::UpdatePosition()
    {
        auto pos = this->getPosition();
        auto offset = sf::Vector2f(pos.x, pos.y);

        auto v_count = vertexArray->getVertexCount();
        for (int i = 0; i < v_count; i++)
        {
            (*vertexArray)[i].position += offset;
        };
    }
}