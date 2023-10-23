#include "inputmanager.hpp"

namespace egl
{
    InputManager *InputManager::pinstance_{nullptr};
    std::mutex InputManager::mutex_;

    InputManager *InputManager::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new InputManager();
        }
        return pinstance_;
    }

    void InputManager::StartEventLoop(sf::RenderWindow *window)
    {
        sf::Event event;
        auto uiManager = UIManager::GetInstance(window);
        while (true)
        {
            while (window->pollEvent(event))
            {
                auto zoomScrollSpeed = .1f;
                switch (event.type)
                {
                case sf::Event::Closed:
                    window->close();
                    std::terminate();
                    return;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window->close();
                        std::terminate();
                        return;
                    }
                    break;
                case sf::Event::MouseWheelScrolled:
                    uiManager->ZoomCamera(event.mouseWheelScroll.delta * zoomScrollSpeed);
                    break;
                default:
                    break;
                }
            }
            auto viewDelta = sf::Vector2f(0.f, 0.f);
            float scrollSpeed = 15.25f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                viewDelta.x -= scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                viewDelta.y -= scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                viewDelta.x += scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                viewDelta.y += scrollSpeed;
            }
            uiManager->MoveCamera(viewDelta);
            std::this_thread::sleep_for(8ms);
        }
    }
}