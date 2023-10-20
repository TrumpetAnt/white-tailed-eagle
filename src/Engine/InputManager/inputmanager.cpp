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
                switch (event.type)
                {
                case sf::Event::Closed:
                    window->close();
                    std::terminate();
                    return;
                case sf::Event::KeyPressed:
                    std::cout << "Key pressed" << std::endl;
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window->close();
                        std::terminate();
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
            auto viewDelta = sf::Vector2f(0.f, 0.f);
            float scrollSpeed = 15.25f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                viewDelta.x -= scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                viewDelta.y -= scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                viewDelta.x += scrollSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                viewDelta.y += scrollSpeed;
            }
            uiManager->MoveCamera(viewDelta);
            std::this_thread::sleep_for(8ms);
        }
    }
}