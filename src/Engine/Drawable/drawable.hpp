#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity/transform.hpp"

namespace egl
{
    class EgDrawable : public sf::Drawable, public sf::Transformable
    {
    private:
        Transform *transform;
        sf::VertexArray vertexArray;

    public:
        EgDrawable(Transform *parentTransform, sf::VertexArray vertexArray) : transform(parentTransform), vertexArray(vertexArray){};

        sf::VertexArray UpdatePosition();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            // apply the transform
            states.transform *= getTransform();

            // draw the vertex array
            target.draw(m_vertices, states);
        }

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
    };
};
