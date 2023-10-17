#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity/transform.hpp"

namespace egl
{
    class Drawable
    {
    private:
        Transform *transform;

    public:
        Drawable(Transform *parentTransform) : transform(parentTransform){};

        sf::VertexArray GetVertexArray();
    };
};
