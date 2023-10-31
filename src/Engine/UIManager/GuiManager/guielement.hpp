#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace egl
{
    class GuiElement
    {
    protected:
        std::vector<GuiElement *> *children = new std::vector<GuiElement *>();
        GuiElement *parent = nullptr;
        sf::Vector2f position;
        sf::Vector2f size = sf::Vector2f(0.f, 0.f);
        sf::Shape *shape = nullptr;
        sf::Text *text = nullptr;
        void (*action)(sf::Mouse::Button) = nullptr;

        void setSizeFromShape();

    public:
        GuiElement(sf::Vector2f position);
        GuiElement(sf::Vector2f position, sf::Text *text);
        GuiElement(sf::Vector2f position, sf::Shape *shape);
        GuiElement(sf::Vector2f position, sf::Shape *shape, void (*action)(sf::Mouse::Button));

        void AddChild(GuiElement *child);
        void SetFillColor(sf::Color color);
        bool ClickAt(sf::Vector2f guiPos, sf::Mouse::Button button);
        void RenderGui(sf::RenderWindow &window);
    };
}