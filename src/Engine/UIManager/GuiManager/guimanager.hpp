#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>
#include <vector>
#include "guielement.hpp"
#include "guielementfactory.hpp"

namespace egl
{
    class GuiManager
    {
    private:
        static GuiManager *pinstance_;
        static std::mutex mutex_;

        std::vector<GuiElement *> *elements = new std::vector<GuiElement *>();

    protected:
        GuiManager();
        ~GuiManager();

    public:
        GuiManager(GuiManager &other) = delete;
        void operator=(const GuiManager &) = delete;
        static GuiManager *GetInstance();

        void AddGuiElement(GuiElement *element);

        bool ClickAt(sf::Vector2i guiPos, sf::Mouse::Button button);

        void RenderGui(sf::RenderWindow &window);
    };
}
