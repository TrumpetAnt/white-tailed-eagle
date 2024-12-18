#include "guielementfactory.hpp"

namespace egl
{
    sf::Shape *GuiElementFactory::ButtonShape(sf::Vector2f pos, sf::Vector2f size)
    {
        auto shape = new sf::RectangleShape(size);
        shape->setPosition(pos);
        shape->setFillColor(sf::Color::White);
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(2.f);
        return shape;
    }

    GuiElement *GuiElementFactory::GetMediumButton(sf::Vector2f position, std::string text, void (*action)(sf::Mouse::Button))
    {
        auto size = sf::Vector2f(200.f, 80.f);
        auto shape = GuiElementFactory::ButtonShape(position, size);
        auto button = new GuiElement(position, shape, action);
        auto textElement = GuiElementFactory::GetTextElement(position, text); // TODO Align text
        button->AddChild(textElement);
        return button;
    }

    GuiElement *GuiElementFactory::GetTextElement(sf::Vector2f position, std::string text)
    {
        auto textElement = new sf::Text();
        textElement->setString(text);

        auto fontManager = FontManager::GetInstance();
        auto font = fontManager->GetFont(FontManager::Fonts::Oswald);
        textElement->setCharacterSize(40);
        textElement->setFont(*font);
        textElement->setFillColor(sf::Color::Black);
        textElement->setOutlineColor(sf::Color::White);
        textElement->setOutlineThickness(1.f);
        textElement->setPosition(position);

        auto guiElement = new GuiElement(position, textElement);
        return guiElement;
    }

    GuiElement *GuiElementFactory::GetCircle(sf::Vector2f position, float radius, sf::Color color)
    {
        auto shape = new sf::CircleShape(radius);
        shape->setFillColor(color);
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(3.f);
        shape->setPosition(position);
        return new GuiElement(position, shape);
    }
}
