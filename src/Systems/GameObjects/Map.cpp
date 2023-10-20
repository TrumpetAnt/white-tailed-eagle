#include "Map.hpp"

namespace egl
{
    Map::Map(int width, int height, std::vector<Tile *> *tiles) : width(width), height(height), tiles(tiles)
    {
        if (width <= 0 || height <= 0 || 1000000 < width * height || tiles == nullptr || tiles->size() != width * height)
        {
            throw std::invalid_argument("Map requires width and height > 0 and width * height < 1000001");
        }
    };

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
}