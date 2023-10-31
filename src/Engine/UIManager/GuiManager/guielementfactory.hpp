#pragma once

#include "guielement.hpp"
#include "fontmanager.hpp"

namespace egl
{
    class GuiElementFactory
    {
    private:
        static sf::Shape *ButtonShape(sf::Vector2f pos, sf::Vector2f size);

    public:
        static GuiElement *GetMediumButton(sf::Vector2f position, std::string text, void (*action)(sf::Mouse::Button));
        static GuiElement *GetTextElement(sf::Vector2f position, std::string text);
        static GuiElement *GetCircle(sf::Vector2f position, float radius, sf::Color color);
    };
}
