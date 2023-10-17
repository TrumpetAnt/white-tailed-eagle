#pragma once

#include <vector>
#include "../../Drawable/drawable.hpp"

namespace egl
{
    class Renderer
    {
    private:
        sf::RenderWindow *window;

    public:
        Renderer(sf::RenderWindow *window) : window(window)
        {
        }

        void Draw(std::vector<EgDrawable *> *drawables);

        void PrepareFrame();

        void FlushFrame();
    };
}