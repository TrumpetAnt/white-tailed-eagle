#include "EntityFactory.hpp"

namespace egl
{
    Tile *EntityFactory::GetTile(sf::Vector2f pos, sf::Vector2i pos_int, TileType type, int height)
    {
        auto res = new Tile(pos_int, height);
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

        auto worldSize = sf::Vector2f(spacing * sqrt3div2 * w, h * .75f * spacing);
        std::cout << "World size: " << worldSize.x << "x" << worldSize.y << std::endl;

        auto heightMap = new NoiseMap(sf::Vector2i(worldSize));
        for (int row = 0; row < h; row++)
        {
            for (int col = 0; col < w; col++)
            {
                auto x_pos = static_cast<float>(col) * spacing * sqrt3div2 + offset + ((row % 2) * spacing * sqrt3div2 / 2);
                auto y_pos = static_cast<float>(row) * spacing * .75f + offset;
                auto worldPos = sf::Vector2f(x_pos, y_pos);
                auto height = heightMap->CalcAt(worldPos - sf::Vector2f(offset, offset));
                std::cout << "Height " << height << " at world pos " << worldPos.x - offset << ", " << worldPos.y - offset << std::endl;
                auto heightIndex = (int)std::floor(height * Map::maxHeight);
                tiles->push_back(GetTile(worldPos, sf::Vector2i(col, row), TileType::Grass, heightIndex));
            }
        }
        *out_tiles = tiles;
        auto res = new Map(w, h, tiles);
        res->AddHeightMap(heightMap);
        return res;
    }

    Battalion *EntityFactory::GetBattalion(int team)
    {
        auto res = new Battalion(team);
        res->AddDrawable();
        return res;
    }

    BattalionProjectile *EntityFactory::GetBattalionProjectile()
    {
        auto res = new BattalionProjectile();
        auto drawable = DrawableFactory::GetTriangle(sf::Vector2f(5.f, 15.f));
        drawable->SetColor(sf::Color::Magenta);
        res->AddDrawable(drawable);
        return res;
    }

    CapturePoint *EntityFactory::GetCapturePoint(int team)
    {
        auto res = new CapturePoint(team);
        res->AddDrawable();
        return res;
    }

    PathSegment *EntityFactory::GetPathSegment()
    {
        return new PathSegment();
    }

    NoiseMap *EntityFactory::GetNoiseMap()
    {
        return new NoiseMap();
    }
}