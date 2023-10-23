#include "Battalion.hpp"

namespace egl
{
    void Battalion::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetCircle(pos);

        drawable->SetColor(sf::Color::Red);
    }

    bool Battalion::IsSelectable()
    {
        return true;
    }

    bool Battalion::AttemptSelect(float x, float y)
    {
        auto distance = getPosition() - sf::Vector2f(x, y);
        return distance.x * distance.x + distance.y * distance.y < 25.f * 25.f;
    }

    void Battalion::Highlight()
    {
        drawable->SetColor(sf::Color::White);
    };

    void Battalion::ResetHighlight()
    {
        drawable->SetColor(sf::Color::Red);
    };
}
