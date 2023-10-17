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
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window->close();
                        std::terminate();
                        return;
                    }
                    std::cout << "Key pressed" << std::endl;
                    break;
                default:
                    break;
                }
            }
            std::this_thread::sleep_for(8ms);
        }
    }
}