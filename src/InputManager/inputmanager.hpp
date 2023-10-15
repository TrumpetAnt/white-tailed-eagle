#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class InputManager
{
private:
    static InputManager *pinstance_;
    static std::mutex mutex_;

protected:
    InputManager()
    {
    }
    ~InputManager() {}

public:
    InputManager(InputManager &other) = delete;
    void operator=(const InputManager &) = delete;
    static InputManager *GetInstance();

    void StartEventLoop(sf::RenderWindow *window);
};
