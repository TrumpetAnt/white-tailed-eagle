#pragma once

#include "../../Systems/GameObjects/Map.hpp"
#include "../../Systems/GameObjects/Tile.hpp"
#include "../Drawable/drawablefactory.hpp"
#include "entity.hpp"
#include "entitybuilder.hpp"

namespace egl
{
    class EntityFactory
    {
    public:
        static Tile *GetTile(sf::Vector2f pos);
        static Map *GetMap(int w, int h);
    };
}