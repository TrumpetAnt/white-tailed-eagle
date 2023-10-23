#pragma once

#include <SFML/Graphics.hpp>

namespace egl
{
    class EgDrawable : public sf::Drawable, public sf::Transformable
    {
    private:
        sf::VertexArray *vertexArray;
        sf::Color color = sf::Color::Magenta;
        sf::Texture *texture = nullptr;

    public:
        EgDrawable(sf::VertexArray *vertexArray) : vertexArray(vertexArray){};

        void SetTexture(sf::Texture *t);
        void SetColor(sf::Color c);
        void UpdatePosition();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();

            if (texture != nullptr)
            {
                states.texture = texture;
            }

            target.draw(*vertexArray, states);
        };
    };
};
