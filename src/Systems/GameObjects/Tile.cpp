#include "Tile.hpp"

namespace egl
{
    void Tile::AddDrawable()
    {
        drawable = DrawableFactory::GetHexagon(&transform);
    }
}