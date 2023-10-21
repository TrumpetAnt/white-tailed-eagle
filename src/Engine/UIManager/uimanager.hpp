#pragma once

#include <mutex>
#include "Renderer/renderer.hpp"
#include "../StateManager/state.hpp"

namespace egl
{
    class UIManager
    {
    private:
        static UIManager *pinstance_;
        static std::mutex mutex_;

        Renderer *renderer;
        sf::RenderWindow *window;
        sf::Vector2f refWindowSize = sf::Vector2f(1600.f, 900.f);
        sf::View view = sf::View(sf::Vector2f(refWindowSize.x / 2, refWindowSize.y / 2), refWindowSize);
        sf::Vector2f cameraDelta = sf::Vector2f(0.f, 0.f);
        float zoomTotal = 1.f;
        sf::Vector2f zoomLimits = sf::Vector2f(0.f, 10.f);

        static std::mutex camera_mutex;
        void SafeMoveCamera(sf::Vector2f delta);
        void SafeZoomCamera(float delta);

    public:
        UIManager(sf::RenderWindow *w);
        UIManager(UIManager &other) = delete;
        void operator=(const UIManager &) = delete;
        static UIManager *GetInstance(sf::RenderWindow *window);

        void ReceiveDrawables(std::vector<EgDrawable *> *drawables);
        void PrepareFrame();
        void FlushFrame();

        void MoveCamera(sf::Vector2f delta);
        void ZoomCamera(float delta);
    };
};