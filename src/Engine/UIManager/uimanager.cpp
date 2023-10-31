#include "uimanager.hpp"

namespace egl
{
    std::mutex UIManager::camera_mutex;
    UIManager *UIManager::pinstance_{nullptr};
    std::mutex UIManager::mutex_;

    UIManager::UIManager(sf::RenderWindow *w)
    {
        window = w;
        window->setView(view);
        renderer = new Renderer(window);

        auto windowSize = window->getSize();
        auto bottom_right = sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)) - sf::Vector2f(300.f, 140.f);
        guiManager->AddGuiElement(GuiElementFactory::GetMediumButton(bottom_right, "Next turn", [](sf::Mouse::Button button) -> void
                                                                     { StateManager::GetInstance()->NextTurn(button); }));
    };

    UIManager *UIManager::GetInstance(sf::RenderWindow *window)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new UIManager(window);
        }
        return pinstance_;
    }

    void UIManager::ReceiveDrawables(std::vector<EgDrawable *> *drawables)
    {
        renderer->Draw(drawables);
    }

    void UIManager::DrawGui()
    {
        guiManager->RenderGui(*window);
    }

    void UIManager::PrepareFrame()
    {
        view.move(cameraDelta.x, cameraDelta.y);
        view.zoom(zoomTotal);
        window->setView(view);
        renderer->PrepareFrame();
        zoomTotal = 1.f;
    }

    void UIManager::FlushFrame()
    {
        SafeMoveCamera(sf::Vector2f(0.f, 0.f));
        renderer->FlushFrame();
    }

    void UIManager::SafeMoveCamera(sf::Vector2f delta)
    {
        std::lock_guard<std::mutex> lock(camera_mutex);
        cameraDelta = delta;
    }

    void UIManager::SafeZoomCamera(float delta)
    {
        std::lock_guard<std::mutex> lock(camera_mutex);
        if (zoomTotal + delta < zoomLimits.x || zoomLimits.y < zoomTotal + delta)
        {
            return;
        }
        zoomTotal += delta;
    }

    void UIManager::MoveCamera(sf::Vector2f delta)
    {
        auto zoomFactor = view.getSize().x / refWindowSize.x;
        SafeMoveCamera(delta * zoomFactor);
    }

    void UIManager::ZoomCamera(float delta)
    {
        SafeZoomCamera(delta);
    }

    sf::Vector2f UIManager::windowToGlobalCoords(sf::Vector2i windowPos)
    {
        auto clickPos = sf::Vector2f(static_cast<float>(windowPos.x), static_cast<float>(windowPos.y));
        auto relPos = sf::Vector2f(clickPos.x / refWindowSize.x, clickPos.y / refWindowSize.y);

        auto viewWorldPos = sf::Vector2f(view.getCenter().x - view.getSize().x / 2.f, view.getCenter().y - view.getSize().y / 2.f);
        return sf::Vector2f(viewWorldPos.x + view.getSize().x * relPos.x, viewWorldPos.y + view.getSize().y * relPos.y);
    }

    void UIManager::ClickAt(int x, int y, sf::Mouse::Button button)
    {
        if (guiManager->ClickAt(sf::Vector2i(x, y), button))
        {
            return;
        }

        auto worldPos = windowToGlobalCoords(sf::Vector2i(x, y));

        stateManager->ClickAt(worldPos.x, worldPos.y, button);
    }

    void UIManager::MouseAt(sf::Vector2i pos)
    {
        auto inWindowPos = pos; // - window->getPosition();

        auto worldPos = windowToGlobalCoords(inWindowPos);
        stateManager->MouseAt(worldPos.x, worldPos.y);
    }
}