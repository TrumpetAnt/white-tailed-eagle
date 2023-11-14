#include "TileBorder.hpp"
#include "Tile.hpp"

namespace egl
{
    TileBorder::TileBorder() : Entity(EntityType::E_TileBorder)
    {
        auto tex = TextureManager::GetInstance()->LoadTexture("assets/img/HomeBrew/SlopeTexture.png");
        drawable = DrawableFactory::GetRectangle(sf::Vector2f(Tile::radius, 10.f), sf::Vector2f(Tile::radius, 10.f));
        drawable->SetTexture(tex);
    }
}
