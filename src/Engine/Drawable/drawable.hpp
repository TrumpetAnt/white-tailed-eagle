#pragma once

#include <SFML/Graphics.hpp>

namespace egl
{
    class EgDrawable : public sf::Drawable, public sf::Transformable
    {
    private:
        sf::VertexArray *vertexArray;

    public:
        EgDrawable(sf::VertexArray *vertexArray) : vertexArray(vertexArray){};

        void UpdatePosition();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();

            target.draw(*vertexArray, states);
        };
    };
};
