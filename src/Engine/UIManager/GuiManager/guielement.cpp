#include "guielement.hpp"

namespace egl
{
    GuiElement::GuiElement(sf::Vector2f position) : position(position) {}

    GuiElement::GuiElement(sf::Vector2f position, sf::Text *text) : position(position), text(text) {}

    GuiElement::GuiElement(sf::Vector2f position, sf::Shape *shape) : position(position), shape(shape)
    {
        setSizeFromShape();
    }

    GuiElement::GuiElement(sf::Vector2f position, sf::Shape *shape, void (*action)(sf::Mouse::Button)) : position(position), shape(shape), action(action)
    {
        setSizeFromShape();
    }

    void GuiElement::setSizeFromShape()
    {
        if (shape == nullptr)
        {
            return;
        }
        auto x = shape->getLocalBounds();
        size = sf::Vector2f(x.width, x.height);
    }

    void GuiElement::AddChild(GuiElement *child)
    {
        children->push_back(child);
    }

    bool GuiElement::ClickAt(sf::Vector2f guiPos, sf::Mouse::Button button)
    {
        if (shape != nullptr)
        {
            auto top_left = shape->getPosition();
            if (top_left.x <= guiPos.x &&
                guiPos.x <= top_left.x + size.x &&
                top_left.y <= guiPos.y &&
                guiPos.y <= top_left.y + size.y)
            {
                action(button);
                return true;
            }
        }

        for (auto child : *children)
        {
            if (child->ClickAt(guiPos, button))
            {
                return true;
            }
        }
        return false;
    }

    void GuiElement::RenderGui(sf::RenderWindow &window)
    {
        if (shape != nullptr)
        {
            window.draw(*shape);
        }
        if (text != nullptr)
        {
            window.draw(*text);
        }
        for (auto child : *children)
        {
            child->RenderGui(window);
        }
    }
}
