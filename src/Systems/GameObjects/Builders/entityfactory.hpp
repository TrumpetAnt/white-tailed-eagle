#pragma once

#include "../Map.hpp"
#include "../Tile.hpp"
#include "../../../Engine/Drawable/drawablefactory.hpp"
#include "../../../Engine/Entity/entity.hpp"
#include "entitybuilder.hpp"
#include "../TileType.hpp"
#include "../Units/Battalion.hpp"

namespace egl
{
    class EntityFactory
    {
    public:
        static Tile *GetTile(sf::Vector2f pos);
        static Map *GetMap(int w, int h);

        static Battalion *GetBattalion();
    };
}