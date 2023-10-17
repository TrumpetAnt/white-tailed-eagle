#pragma once

#include "Renderer/renderer.hpp"
#include "../StateManager/state.hpp"

namespace egl
{
    class UIManager
    {
    private:
        Renderer *renderer;
        sf::RenderWindow *window;

    public:
        UIManager(sf::RenderWindow *window) : window(window)
        {
            renderer = new Renderer(window);
        };

        void ReceiveDrawables(std::vector<Drawable *> *drawables);
        void PrepareFrame();
        void FlushFrame();
    };
}