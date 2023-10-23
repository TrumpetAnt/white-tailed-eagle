#include "Map.hpp"

namespace egl
{
    Map::Map(int width, int height, std::vector<Tile *> *tiles) : width(width), height(height), tiles(tiles), Entity(EntityType::E_Map)
    {
        if (width <= 0 || height <= 0 || 1000000 < width * height || tiles == nullptr || tiles->size() != width * height)
        {
            throw std::invalid_argument("Map requires width and height > 0 and width * height < 1000001");
        }
    };

    bool Map::checkBounds(int x, int y)
    {
        return 0 <= x && 0 <= y && x <= width && y <= height;
    }

    bool Map::IsDrawable()
    {
        return true;
    }

    void Map::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        for (auto tile : *tiles)
        {
            tile->ConcatDrawable(res);
        }
    }

    void Map::AddBattalionAt(Battalion *bat, int x, int y)
    {
        if (!checkBounds(x, y))
        {
            return;
        }
        auto tile = tiles->at(y * width + x);
        tile->AddBattalion(bat);
        bat->setPosition(tile->getPosition());
        bat->UpdateTransforms();
    }
}