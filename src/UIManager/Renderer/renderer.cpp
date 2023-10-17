#include "renderer.hpp"

namespace egl
{
    void Renderer::Draw(std::vector<Drawable *> *drawables)
    {
        for (auto d : *drawables)
        {
            window->draw(d->GetVertexArray());
        }

        drawables->clear();
        delete drawables;
    }

    void Renderer::PrepareFrame()
    {
        window->clear();
    }

    void Renderer::FlushFrame()
    {
        window->display();
    }
}