#include "Map.hpp"

namespace egl
{
    Map::Map(int width, int height, std::vector<Tile *> *tiles) : width(width), height(height), tiles(tiles), Entity(EntityType::E_Map)
    {
        if (width <= 0 || height <= 0 || 1000000 < width * height || tiles == nullptr || tiles->size() != width * height)
        {
            throw std::invalid_argument("Map requires width and height > 0 and width * height < 1000001");
        }
        for (auto tile : *tiles)
        {
            this->AttachChild(tile);
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

    void Map::HighlightTilesAround(int x, int y, int r)
    {
        if (!checkBounds(x, y))
        {
            return;
        }

        for (int row = std::max(y - r, 0); row < y + r + 1 && row < height; row++)
        {
            for (int col = std::max(x - r, 0); col < x + r + 1 && col < width; col++)
            {
                auto t = tiles->at(row * width + col);
                t->Highlight();
                highlightedTiles->push_back(t);
            }
        }
    }

    void Map::ResetAllHighlightedTiles()
    {
        for (auto tile : *highlightedTiles)
        {
            tile->ResetHighlight();
        }
        highlightedTiles->clear();
    }
}