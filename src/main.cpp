#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <X11/Xlib.h>
#include <iostream>
#include <math.h>

#include "Engine/InputManager/inputmanager.hpp"
#include "Engine/StateManager/statemanager.hpp"
#include "Engine/UIManager/uimanager.hpp"
#include "Systems/GameObjects/Tile.hpp"

int main()
{
    XInitThreads();
    auto window = sf::RenderWindow{{1600u, 900u}, "White-Tailed Eagle"};
    window.setFramerateLimit(144);

    auto inputManager = egl::InputManager::GetInstance();
    std::thread inputThread(&egl::InputManager::StartEventLoop, inputManager, &window);
    inputThread.detach();

    auto stateManager = egl::StateManager::GetInstance();
    auto uiManager = egl::UIManager::GetInstance(&window);

    float targetFps = 60;
    float nanoPerFrame = 1000000000 / targetFps;
    auto durationPerFrame = std::chrono::nanoseconds(static_cast<int>(nanoPerFrame));

    long frameCount = 0;
    while (window.isOpen())
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        uiManager->PrepareFrame();
        auto drawables = stateManager->GetDrawables();
        uiManager->ReceiveDrawables(drawables);
        uiManager->FlushFrame();

        auto t1 = std::chrono::high_resolution_clock::now();
        auto fs = t1 - t0;

        if (fs < durationPerFrame)
        {
            std::this_thread::sleep_for(durationPerFrame - fs);
        }
        else
        {
            std::cout << ". Duration " << fs.count() << " exceeded expected duration " << durationPerFrame.count() << std::endl;
        }
        frameCount += 1;
    }
}