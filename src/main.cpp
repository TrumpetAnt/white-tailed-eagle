#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <X11/Xlib.h>
#include <iostream>
#include <math.h>

#include "InputManager/inputmanager.hpp"

int main()
{
    XInitThreads();
    auto inputManager = InputManager::GetInstance();
    auto window = sf::RenderWindow{{1600u, 900u}, "White-Tailed Eagle"};
    window.setFramerateLimit(144);

    std::thread inputThread(&InputManager::StartEventLoop, inputManager, &window);
    inputThread.detach();

    float targetFps = 60;
    float nanoPerFrame = 1000000000 / targetFps;
    auto durationPerFrame = std::chrono::nanoseconds(static_cast<int>(nanoPerFrame));

    sf::VertexArray triangle(sf::Triangles, 3);

    // define the position of the triangle's points
    triangle[0].position = sf::Vector2f(10.f, 10.f);
    triangle[1].position = sf::Vector2f(100.f, 10.f);
    triangle[2].position = sf::Vector2f(100.f, 100.f);

    // define the color of the triangle's points
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    long frameCount = 0;
    float framesPerRotation = 120;
    auto framesPerRotation_i = static_cast<int>(framesPerRotation);
    while (window.isOpen())
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        window.clear();
        auto rot_radius = 100.f;
        auto rotation = static_cast<float>(frameCount % framesPerRotation_i) / framesPerRotation * 2 * M_PI;
        auto x_rot = rot_radius * cos(rotation);
        auto y_rot = rot_radius * sin(rotation);
        triangle[0].position = sf::Vector2f(100.f + x_rot, 100.f + y_rot);
        triangle[1].position = sf::Vector2f(200.f, 100.f);
        triangle[2].position = sf::Vector2f(200.f + x_rot, 200.f + y_rot);
        window.draw(triangle);
        window.display();

        auto t1 = std::chrono::high_resolution_clock::now();
        auto fs = t1 - t0;
        std::cout << "Frame: " << frameCount;
        if (fs < durationPerFrame)
        {
            std::cout << std::endl;
            std::this_thread::sleep_for(durationPerFrame - fs);
        }
        else
        {
            std::cout << " duration exceeded allowed duration" << std::endl;
        }
        frameCount += 1;
    }
}