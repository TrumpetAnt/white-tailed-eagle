#include "uimanager.hpp"

namespace egl
{
    void UIManager::ReceiveDrawables(std::vector<Drawable *> *drawables)
    {
        renderer->Draw(drawables);
    }

    void UIManager::PrepareFrame()
    {
        renderer->PrepareFrame();
    }

    void UIManager::FlushFrame()
    {
        renderer->FlushFrame();
    }
}