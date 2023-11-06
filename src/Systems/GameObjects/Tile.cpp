#include "Tile.hpp"
#include "Map.hpp"
#include "../../Engine/StateManager/statemanager.hpp"

namespace egl
{
    sf::Vector2i Tile::GetDiscretePos()
    {
        return pos;
    }

    std::string RandomGrassTexture(int i)
    {
        switch (i)
        {
        case 2:
            return "assets/img/PNG/Tiles/Terrain/Grass/grass_16.png";
        case 3:
            return "assets/img/PNG/Tiles/Terrain/Grass/grass_11.png";
        case 4:
            return "assets/img/PNG/Tiles/Terrain/Grass/grass_05.png";
        case 5:
            return "assets/img/PNG/Tiles/Terrain/Grass/grass_10.png";
        case 6:
            return "assets/img/PNG/Tiles/Terrain/Grass/grass_15.png";
        default:
            break;
        }
        return "assets/img/PNG/Tiles/Terrain/Grass/grass_05.png";
    }

    sf::Texture *TileTypeToTexture(TileType type)
    {
        auto tm = TextureManager::GetInstance();
        int tileTex = rand() % 3 + rand() % 3 + 2;
        switch (type)
        {
        case TileType::Grass:
            return tm->LoadTexture(RandomGrassTexture(tileTex));
        default:
            throw std::invalid_argument("Unhandled switch case");
        }
    }

    void Tile::AddDrawable(TileType type)
    {
        auto pos = getPosition();
        drawable = DrawableFactory::GetHexagon(pos, Tile::radius);

        tileType = type;
        drawable->SetTexture(TileTypeToTexture(type));

        int variance = 40;
        auto c = sf::Color::White; //::Color(84 + (rand() % variance), 201 + (rand() % variance), 60 + (rand() % variance));
        drawable->SetColor(c);
        baseColor = c;

        outline = DrawableFactory::GetHexagonOutline(pos, Tile::radius, outlineBaseColor);
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

    float Tile::GetMoveCost(int team)
    {
        if (battalion != nullptr && battalion->GetTeam() != team)
        {
            return 100.f;
        }
        return moveCost;
    }

    void Tile::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        if (IsDrawable())
        {
            UpdateTransforms();
            res->push_back(drawable);
            if (displayOutline)
            {
                outline->setPosition(getPosition());
                res->push_back(outline);
            }
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
        outline->SetColor(sf::Color::White);
    };

    void Tile::AlternateHighlight()
    {
        outline->SetColor(sf::Color::Red);
    }

    void Tile::ResetHighlight()
    {
        outline->SetColor(outlineBaseColor);
    };

    bool Tile::InteractWithEntity(Entity *selected)
    {
        switch (selected->GetEntityType())
        {
        case EntityType::E_Battalion:
            if (battalion != nullptr)
            {
                return false;
            }
            battalion = static_cast<Battalion *>(selected);
            auto map = static_cast<Map *>(parent);
            if (map->AttemptMoveBattalionToTile(battalion, this))
            {
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

    void Tile::Hover()
    {
        auto selected = StateManager::GetInstance()->GetSelected();
        if (selected == nullptr || selected->GetEntityType() != EntityType::E_Battalion)
        {
            return;
        }
        auto selected_bat = static_cast<Battalion *>(selected);
        auto actions = selected_bat->GetPossibleActions();
        if (actions == nullptr)
        {
            return;
        }
        for (auto action : *actions)
        {
            if (action.first == this)
            {
                auto bat_at_target = GetBattalion();
                PathSegmentPool::GetInstance()
                    ->MarkMovePath(action.second, bat_at_target != nullptr && bat_at_target->GetTeam() != selected_bat->GetTeam());
            }
        }
    };

    void Tile::StopHover()
    {
        PathSegmentPool::GetInstance()->UnMarkPath();
    };
}