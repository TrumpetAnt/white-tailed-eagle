#include "Battalion.hpp"
#include "../Map.hpp"
#include "../Tile.hpp"

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
        auto tile = static_cast<Tile *>(parent);
        auto m = static_cast<Map *>(tile->parent);
        auto pos = tile->GetDiscretePos();
        m->HighlightTilesAround(pos.x, pos.y, GetMovementPoints());
    }

    void Battalion::ResetHighlight()
    {
        drawable->SetColor(sf::Color::Red);
        auto m = static_cast<Map *>(parent->parent);
        m->ResetAllHighlightedTiles();
    }

    uint Battalion::GetMovementPoints()
    {
        return movementPoints;
    }

    Tile *Battalion::GetParentTile()
    {
        return static_cast<Tile *>(parent);
    }
}
