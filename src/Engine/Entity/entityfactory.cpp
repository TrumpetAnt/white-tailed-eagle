#include "entityfactory.hpp"

namespace egl
{
    Tile *EntityFactory::GetTile(sf::Vector3f pos)
    {
        auto res = new Tile();
        res->AddDrawable();
        return res;
    }

    Map *EntityFactory::GetMap(int w, int h)
    {
        auto tiles = new std::vector<Tile *>(w * h);
        int c = 0;
        for (auto tile : *tiles)
        {
            tile = GetTile(sf::Vector3f(static_cast<float>(c % w), static_cast<float>(c / w), 0.f));
        }
        return new Map(w, h, tiles);
    }
}