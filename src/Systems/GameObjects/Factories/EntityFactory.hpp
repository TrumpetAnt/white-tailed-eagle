#pragma once

#include "../Map.hpp"
#include "../Tile.hpp"
#include "../../../Engine/Drawable/drawablefactory.hpp"
#include "../../../Engine/Entity/entity.hpp"
#include "../TileType.hpp"
#include "../Units/Battalion.hpp"
#include "../Units/BattalionProjectile.hpp"
#include "../CapturePoint.hpp"
#include "../Path/PathSegment.hpp"

namespace egl
{
    class EntityFactory
    {
    public:
        static Tile *GetTile(sf::Vector2f pos, sf::Vector2i pos_int);
        static Map *GetMap(int w, int h, std::vector<Tile *> **out_tiles);
        static Battalion *GetBattalion(int team);
        static BattalionProjectile *GetBattalionProjectile();
        static CapturePoint *GetCapturePoint(int team);
        static PathSegment *GetPathSegment();
    };
}