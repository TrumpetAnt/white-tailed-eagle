#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <X11/Xlib.h>
#include <iostream>
#include <math.h>
#include <filesystem>
#include <fstream>

#include "Engine/InputManager/inputmanager.hpp"
#include "Engine/StateManager/statemanager.hpp"
#include "Engine/UIManager/uimanager.hpp"
#include "Engine/UIManager/GuiManager/fontmanager.hpp"
#include "Systems/GameObjects/Tile.hpp"

int main()
{
    XInitThreads();
    // Setup window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    auto window = sf::RenderWindow{{1600u, 900u}, "White-Tailed Eagle", sf::Style::Default, settings};
    window.setFramerateLimit(144);

    // Load fonts
    auto currentPath = std::filesystem::current_path().string();
    currentPath = currentPath.substr(0, currentPath.length() - 4);
    auto fontManager = egl::FontManager::GetInstance();
    if (!fontManager->LoadFont("assets/fonts/", egl::FontManager::Fonts::Oswald))
    {
        return -1;
    }

    // Setup input manager thread
    auto inputManager = egl::InputManager::GetInstance();
    std::thread inputThread(&egl::InputManager::StartEventLoop, inputManager, &window);
    inputThread.detach();

    // Setup state and ui manager
    auto stateManager = egl::StateManager::GetInstance();
    auto uiManager = egl::UIManager::GetInstance(&window);

    // Frame drop detection
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
        uiManager->DrawGui();
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