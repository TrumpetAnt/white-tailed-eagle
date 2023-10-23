#pragma once

#include <vector>
#include <stdexcept>
#include <unordered_map>

#include "Tile.hpp"
#include "EntityType.hpp"
#include "MinHeap.hpp"

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
        void GetTileNeighbours(std::vector<Tile *> *out_vec, Tile *target);
        int PosToIndex(sf::Vector2i pos);
        std::vector<Tile *> *GetTileSurroundings(Tile *target, int radius);

    public:
        Map(int width, int height, std::vector<Tile *> *tiles);
        int getWidth() { return width; }
        int getHeight() { return height; }

        bool IsDrawable() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;

        void AddBattalionAt(Battalion *bat, int x, int y);
        void HighlightTilesAround(int x, int y, int r);
        void ResetAllHighlightedTiles();

        std::vector<Tile *> *FindPath(Tile *source, sf::Vector2i target, int movementPoints = 9999999);
    };
};