#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../../../Engine/Drawable/drawablefactory.hpp"
#include "../../../Engine/TextureManager/texturemanager.hpp"
#include "TileType.hpp"
#include "../EntityType.hpp"

namespace egl
{
    class Tile;
    class TileBorder : public Entity
    {

    public:
        TileBorder();
    };
}