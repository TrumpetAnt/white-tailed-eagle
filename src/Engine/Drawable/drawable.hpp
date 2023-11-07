#pragma once

#include <SFML/Graphics.hpp>

namespace egl
{
    class EgDrawable : public sf::Drawable, public sf::Transformable
    {
    private:
        sf::Texture *texture = nullptr;

    protected:
        sf::VertexArray *vertexArray;
        sf::Color color = sf::Color::Magenta;
        int layer = 0;

    public:
        EgDrawable(sf::VertexArray *vertexArray) : vertexArray(vertexArray){};

        int GetLayer();
        void SetLayer(int layer);
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
