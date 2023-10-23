#pragma once

#include <vector>
#include <stdexcept>

#include "Tile.hpp"

namespace egl
{
    class Map : public Entity
    {
    private:
        std::vector<Tile *> *tiles;
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
    };
};