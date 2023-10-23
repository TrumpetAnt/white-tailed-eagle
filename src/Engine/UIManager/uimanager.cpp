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

    void UIManager::ClickAt(int x, int y, sf::Mouse::Button button)
    {
        // std::cout << "Click at view pos (" << x << ", " << y << ") " << button << std::endl;

        auto clickPos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
        auto relPos = sf::Vector2f(clickPos.x / refWindowSize.x, clickPos.y / refWindowSize.y);

        // std::cout << "Click at rel view pos (" << relPos.x << ", " << relPos.y << ")" << std::endl;

        auto zoomFactor = view.getSize().x / refWindowSize.x;
        // std::cout << "Center: ("
        //           << view.getCenter().x
        //           << ", "
        //           << view.getCenter().y
        //           << ")"
        //           << std::endl;

        // std::cout << "View size world pos: ("
        //           << view.getSize().x * zoomFactor
        //           << ", "
        //           << view.getSize().y * zoomFactor
        //           << ")" << std::endl;

        auto viewWorldPos = sf::Vector2f(view.getCenter().x - view.getSize().x * zoomFactor / 2.f, view.getCenter().y - view.getSize().y * zoomFactor / 2.f);
        // std::cout
        //     << "Top left world pos: ("
        //     << viewWorldPos.x
        //     << ", "
        //     << viewWorldPos.y
        //     << ")" << std::endl;

        auto worldPos = sf::Vector2f(viewWorldPos.x + view.getSize().x * zoomFactor * relPos.x, viewWorldPos.y + view.getSize().y * zoomFactor * relPos.y);
        // std::cout << "World pos rel top left ("
        //           <<
        //           << ", "
        //           <<
        //           << " )" << std::endl;

        // std::cout << "Click at world pos (" << x << ", " << y << ") " << std::endl;

        stateManager->ClickAt(worldPos.x, worldPos.y, button);
    }
}