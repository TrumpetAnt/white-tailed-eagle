#include "Tile.hpp"

namespace egl
{
    void Tile::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetHexagon(pos);
    }
}