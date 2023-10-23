#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/Drawable/drawablefactory.hpp"
#include "../../Engine/TextureManager/texturemanager.hpp"
#include "TileType.hpp"

namespace egl
{
    class Tile : public Entity
    {
    private:
        TileType tileType;

    public:
        void AddDrawable(TileType type);
    };
}