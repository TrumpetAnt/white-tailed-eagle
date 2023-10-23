#include "Tile.hpp"

namespace egl
{
    sf::Texture *TileTypeToTexture(TileType type)
    {
        auto tm = TextureManager::GetInstance();
        switch (type)
        {
        case TileType::Grass:
            return tm->LoadTexture("assets/img/grasssssss.png");
        default:
            throw std::invalid_argument("Unhandled switch case");
        }
    }

    void Tile::AddDrawable(TileType type)
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetHexagon(pos);

        tileType = type;
        // drawable->SetTexture(TileTypeToTexture(type));

        int variance = 20;
        auto c = sf::Color(84 + (rand() % variance), 201 + (rand() % variance), 60 + (rand() % variance));
        drawable->SetColor(c);
    }

    void Tile::AddBattalion(Battalion *bat)
    {
        battalion = bat;
    }

    void Tile::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        if (IsDrawable())
        {
            drawable->setPosition(getPosition());
            res->push_back(drawable);
            if (battalion != nullptr && battalion->IsDrawable())
            {
                battalion->ConcatDrawable(res);
            }
        }
    }
}