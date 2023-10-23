#include "EntityFactory.hpp"

namespace egl
{
    Tile *EntityFactory::GetTile(sf::Vector2f pos, sf::Vector2i pos_int)
    {
        auto res = new Tile(pos_int);
        res->AddDrawable(TileType::Grass);
        res->setPosition(pos);
        return res;
    }

    Map *EntityFactory::GetMap(int w, int h, std::vector<Tile *> **out_tiles)
    {
        auto tiles = new std::vector<Tile *>();
        float offset = 100.f;
        float spacing = 80.f;
        float sqrt3div2 = 0.86602540378f;
        for (int row = 0; row < h; row++)
        {
            for (int col = 0; col < w; col++)
            {
                auto x_pos = static_cast<float>(col) * spacing * .75f + offset;
                auto y_pos = static_cast<float>(row) * spacing * sqrt3div2 + offset + ((col % 2) * spacing * sqrt3div2 / 2);
                tiles->push_back(GetTile(sf::Vector2f(x_pos, y_pos), sf::Vector2i(col, row)));
            }
        }
        *out_tiles = tiles;
        return new Map(w, h, tiles);
    }

    Battalion *EntityFactory::GetBattalion()
    {
        auto res = new Battalion();
        res->AddDrawable();
        return res;
    }
}