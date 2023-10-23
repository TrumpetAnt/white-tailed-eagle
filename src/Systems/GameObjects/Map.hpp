#pragma once

#include <vector>
#include <stdexcept>

#include "Tile.hpp"
#include "EntityType.hpp"

namespace egl
{
    class Map : public Entity
    {
    private:
        std::vector<Tile *> *tiles;
        std::vector<Tile *> *highlightedTiles = new std::vector<Tile *>();
        int width;
        int height;

        bool checkBounds(int x, int y);

    public:
        Map(int width, int height, std::vector<Tile *> *tiles);
        int getWidth() { return width; }
        int getHeight() { return height; }

        bool IsDrawable() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;

        void AddBattalionAt(Battalion *bat, int x, int y);
        void HighlightTilesAround(int x, int y, int r);
        void ResetAllHighlightedTiles();
    };
};