#pragma once

#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

#include "Tile.hpp"
#include "EntityType.hpp"
#include "MinHeap.hpp"
#include "CapturePoint.hpp"
#include "Path/PathSegmentPool.hpp"

namespace egl
{
    typedef std::pair<Tile *, std::vector<Tile *> *> action_t;

    class StateManager;
    class Map : public Entity
    {
    private:
        std::vector<Tile *> *tiles;
        std::vector<Tile *> *highlightedTiles = new std::vector<Tile *>();
        int width;
        int height;
        std::unordered_map<int, std::unordered_set<Battalion *> *> *zoneOfControlMap;

        bool checkBounds(int x, int y);
        void GetTileNeighbourPositions(sf::Vector2i *array, int y);
        void GetTileNeighbours(std::vector<Tile *> *out_vec, Tile *target);
        int PosToIndex(sf::Vector2i pos);
        std::vector<Tile *> *GetTileSurroundings(Tile *target, int radius);
        void HighlightTile(Tile *tile);

        void AddZoneOfControlForBattalion(Battalion *bat);
        bool InZoneOfControl(int i, int team);

    public:
        Map(int width, int height, std::vector<Tile *> *tiles);
        int getWidth() { return width; }
        int getHeight() { return height; }

        bool IsDrawable() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;

        // Setup
        void AddBattalionAt(Battalion *bat, int x, int y);
        void AddCapturePointAt(CapturePoint *cp, int x, int y);

        // ~~ UX Highlights ~~
        void HighlightTilesAround(int x, int y, int r);
        void HighlightTiles(std::vector<Tile *> *tiles);
        void HighlightActions(std::vector<action_t> *actions);
        void ResetAllHighlightedTiles();

        bool AttemptMoveBattalionToTile(Battalion *bat, Tile *tile);

        // ~~ Zone of Control
        void RemoveZoneOfControlFromBattalion(Battalion *bat);

        std::vector<action_t> *GetBattalionActions(int x, int y, int movementPoints, int team);
        float CostToTile(std::vector<Tile *> *path);

        std::vector<Tile *> *FindPaths(Tile *source, sf::Vector2i target, int movementPoints = 9999999);
    };
};