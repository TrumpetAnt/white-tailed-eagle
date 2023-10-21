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
}