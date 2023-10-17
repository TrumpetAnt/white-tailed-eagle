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

    public:
        Map(int width, int height, std::vector<Tile *> *tiles);
        int getWidth() { return width; }
        int getHeight() { return height; }

        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
    };
};