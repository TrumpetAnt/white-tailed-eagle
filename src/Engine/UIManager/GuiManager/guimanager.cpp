#include "guimanager.hpp"

namespace egl
{
    GuiManager *GuiManager::pinstance_{nullptr};
    std::mutex GuiManager::mutex_;

    GuiManager *GuiManager::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new GuiManager();
        }
        return pinstance_;
    }

    GuiManager::GuiManager()
    {
    }

    void GuiManager::AddGuiElement(GuiElement *element)
    {
        elements->push_back(element);
    }

    bool GuiManager::ClickAt(sf::Vector2i guiPos, sf::Mouse::Button button)
    {
        auto pos = sf::Vector2f(static_cast<float>(guiPos.x), static_cast<float>(guiPos.y));

        for (auto guiElement : *elements)
        {
            if (guiElement->ClickAt(pos, button))
            {
                return true;
            }
        }
        return false;
    }

    void GuiManager::RenderGui(sf::RenderWindow &window)
    {
        for (auto guiElement : *elements)
        {
            guiElement->RenderGui(window);
        }
    }
}
