#include "drawable.hpp"

namespace egl
{
    void EgDrawable::UpdatePosition()
    {
        auto pos = this->getPosition();
        auto offset = sf::Vector2f(pos.x, pos.y);

        auto v_count = vertexArray->getVertexCount();
        for (int i = 0; i < v_count; i++)
        {
            (*vertexArray)[v_count].position += offset;
        };
    }
}