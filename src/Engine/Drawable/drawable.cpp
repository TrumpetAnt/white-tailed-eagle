#include "drawable.hpp"

namespace egl
{
    sf::VertexArray EgDrawable::UpdatePosition()
    {
        auto pos = transform->GetPosition();
        auto offset = sf::Vector2f(pos.x, pos.y);

        auto v_count = vertexArray.getVertexCount();
        for (int i = 0; i < v_count; i++)
        {
            vertexArray[v_count].position += offset;
        };

        m_vertices = vertexArray;
    }
}