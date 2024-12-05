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
#include "Systems/GameObjects/Tile/Tile.hpp"

int main(int argc, char **argv)
{
    XInitThreads();
    auto nosfml = argc > 1;

    // Setup window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow *window = nullptr;
    if (!nosfml)
    {
        window = new sf::RenderWindow{{1600u, 900u}, "White-Tailed Eagle", sf::Style::Default, settings};
        window->setPosition(sf::Vector2i(10, 10));
        window->setFramerateLimit(144);
    }

    // Load fonts
    auto currentPath = std::filesystem::current_path().string();
    currentPath = currentPath.substr(0, currentPath.length() - 4);
    auto fontManager = egl::FontManager::GetInstance();
    if (!fontManager->LoadFont("assets/fonts/", egl::FontManager::Fonts::Oswald))
    {
        return -1;
    }

    // Setup input manager thread
    if (!nosfml)
    {
        auto inputManager = egl::InputManager::GetInstance();
        std::thread inputThread(&egl::InputManager::StartEventLoop, inputManager, window);
        inputThread.detach();
    }

    // Setup state and ui manager
    auto stateManager = egl::StateManager::GetInstance();

    egl::UIManager *uiManager = nullptr;
    if (!nosfml)
    {
        uiManager = egl::UIManager::GetInstance(window);
    }

    // Frame drop detection
    float targetFps = 60;
    float nanoPerFrame = 1000000000 / targetFps;
    auto durationPerFrame = std::chrono::nanoseconds(static_cast<int>(nanoPerFrame));

    long frameCount = 0;
    while (!nosfml && window->isOpen())
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        uiManager->PrepareFrame();

        auto drawables = stateManager->GetDrawables();
        uiManager->ReceiveDrawables(drawables);

        uiManager->DrawGui();
        uiManager->FlushFrame(); // @todo: Alternate draw frames and flush with lock as to not flush between simulation steps

        drawables->clear();
        delete drawables;

        auto t1 = std::chrono::high_resolution_clock::now();
        auto fs = t1 - t0;

        if (fs < durationPerFrame)
        {
            std::this_thread::sleep_for(durationPerFrame - fs);
        }
        else
        {
            // std::cout << ". Duration " << fs.count() << " exceeded expected duration " << durationPerFrame.count() << std::endl;
        }
        frameCount += 1;

        if (nosfml && frameCount == 10)
        {
            stateManager->NextTurn(sf::Mouse::Button::Left);
        }
    }
}