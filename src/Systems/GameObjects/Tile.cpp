#include "Tile.hpp"
#include "Map.hpp"

namespace egl
{
    sf::Vector2i Tile::GetDiscretePos()
    {
        return pos;
    }

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
        auto pos = getPosition();
        drawable = DrawableFactory::GetHexagon(pos, Tile::radius);

        tileType = type;
        // drawable->SetTexture(TileTypeToTexture(type));

        int variance = 40;
        auto c = sf::Color(84 + (rand() % variance), 201 + (rand() % variance), 60 + (rand() % variance));
        drawable->SetColor(c);
        baseColor = c;
    }

    void Tile::AddBattalion(Battalion *bat)
    {
        battalion = bat;
        auto parent = bat->GetParentTile();
        if (parent != nullptr)
        {
            if (parent == this)
            {
                return;
            }
            parent->ClearBattalion();
        }
        AttachChild(bat);
        battalion->SetPosition(getPosition());
    }

    Battalion *Tile::GetBattalion()
    {
        return battalion;
    }

    void Tile::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        if (IsDrawable())
        {
            drawable->setPosition(getPosition());
            res->push_back(drawable);
        }
    }

    bool Tile::IsSelectable()
    {
        return true;
    }
    float topBound(float y)
    {
        float sqrt3div2 = 0.86602540378f;
        return sqrt3div2 - y;
    }

    float lowerBound(float y)
    {
        float sqrt3div2 = 0.86602540378f;
        return sqrt3div2 + y;
    }

    float upperRightBound(float x, float y)
    {
        float sqrt3 = 0.86602540378f * 2;
        return sqrt3 - x * sqrt3 - y;
    }

    float lowerRightBound(float x, float y)
    {
        float sqrt3 = 0.86602540378f * 2;
        return sqrt3 - x * sqrt3 + y;
    }

    float upperLeftBound(float x, float y)
    {
        float sqrt3 = 0.86602540378f * 2;
        return sqrt3 + x * sqrt3 - y;
    }

    float lowerLeftBound(float x, float y)
    {
        float sqrt3 = 0.86602540378f * 2;
        return sqrt3 + x * sqrt3 + y;
    }

    bool isInHexagon(sf::Vector2f scaledCenter)
    {
        return topBound(scaledCenter.y) > 0 &&
               lowerBound(scaledCenter.y) > 0 &&
               upperRightBound(scaledCenter.x, scaledCenter.y) > 0 &&
               lowerRightBound(scaledCenter.x, scaledCenter.y) > 0 &&
               upperLeftBound(scaledCenter.x, scaledCenter.y) > 0 &&
               lowerLeftBound(scaledCenter.x, scaledCenter.y) > 0;
    }

    Entity *Tile::AttemptSelect(float x, float y)
    {
        auto distance = getPosition() - sf::Vector2f(x, y);
        auto radius = 40.f;
        float sqrt3div2 = 0.86602540378f;
        if (radius * radius < distance.x * distance.x + distance.y * distance.y)
        {
            return nullptr;
        };
        if (battalion != nullptr)
        {
            auto bat_select = battalion->AttemptSelect(x, y);
            if (bat_select != nullptr)
            {
                return bat_select;
            }
        }
        if (distance.x * distance.x + distance.y * distance.y < radius * radius * sqrt3div2 * sqrt3div2)
        {
            return this;
        };

        auto scaledCenter = (sf::Vector2f(x, y) - getPosition()) / radius;
        scaledCenter.y = -1 * scaledCenter.y;

        return isInHexagon(scaledCenter)
                   ? this
                   : nullptr;
    }

    void Tile::Highlight()
    {
        drawable->SetColor(baseColor + sf::Color(40.f, 40.f, 40.f));
    };

    void Tile::AlternateHighlight()
    {
        drawable->SetColor(baseColor - sf::Color(0.f, 40.f, 40.f) + sf::Color(100.f, 0.f, 0.f));
    }

    void Tile::ResetHighlight()
    {
        drawable->SetColor(baseColor);
    };

    bool Tile::InteractWithEntity(Entity *e)
    {
        switch (e->GetEntityType())
        {
        case EntityType::E_Battalion:
            if (battalion != nullptr)
            {
                return false;
            }
            battalion = static_cast<Battalion *>(e);
            auto moveRange = battalion->GetMovementPoints();
            if (SqrDistanceToTile(*(battalion->GetParentTile())) < moveRange * moveRange * Tile::radius * Tile::radius * 4)
            {
                battalion->SpendMovementPoints(moveRange);
                AddBattalion(battalion);
                return true;
            }
            break;
        }
        return false;
    };

    void Tile::ClearBattalion()
    {
        DetachChild(battalion);
        battalion = nullptr;
    }

    float Tile::SqrDistanceToTile(const Tile &other)
    {
        auto diff = getPosition() - other.getPosition();
        return diff.x * diff.x + diff.y * diff.y;
    }
}