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

    Entity *Battalion::AttemptSelect(float x, float y)
    {
        auto distance = getPosition() - sf::Vector2f(x, y);
        return distance.x * distance.x + distance.y * distance.y < 25.f * 25.f ? this : nullptr;
    }

    void Battalion::Highlight()
    {
        drawable->SetColor(sf::Color::White);
    }

    void Battalion::ResetHighlight()
    {
        drawable->SetColor(sf::Color::Red);
    }

    void Battalion::AttachToTile(Battalion **tile_bat_ref)
    {
        ClearBatRef();
        bat_ref = tile_bat_ref;
    }

    void Battalion::ClearBatRef()
    {
        if (bat_ref != nullptr)
        {
            *bat_ref = nullptr;
        }
    }
}
