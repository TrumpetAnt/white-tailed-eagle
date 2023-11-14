#include "Tile.hpp"
#include "../Map.hpp"
#include "../../../Engine/StateManager/statemanager.hpp"

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

    void Tile::InitTile()
    {
        auto map = static_cast<Map *>(parent);
        auto out = std::vector<Tile *>();

        sf::Vector2i delta[6];
        map->GetTileNeighbourPositions(delta, pos.y);
        for (int i = 0; i < 6; i++)
        {
            auto n_pos = delta[i] + pos;
            neighbours[i] = map->GetTileAt(n_pos.x, n_pos.y);
        }
        if (neighbours[2] != nullptr && neighbours[2]->GetHeight() < height)
        {
            auto d = borders[0].GetDrawable();
            d->setRotation(d->getRotation() + 180.f);
        }
        if (neighbours[5] != nullptr && neighbours[5]->GetHeight() < height)
        {
            auto d = borders[1].GetDrawable();
            d->setRotation(d->getRotation() + 180.f);
        }
        if (neighbours[4] != nullptr && neighbours[4]->GetHeight() > height)
        {
            auto d = borders[2].GetDrawable();
            d->setRotation(d->getRotation() + 180.f);
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
        auto maxHeight = (float)Map::maxHeight;
        auto floor = 200.f;
        unsigned int floorI = 200;

        auto delta = (unsigned int)std::round(1.f / maxHeight * (255.f - floor));
        auto distToMax = (unsigned int)height;

        c = sf::Color(delta * distToMax + floorI, delta * distToMax + floorI, delta * distToMax + floorI, 255);

        drawable->SetColor(c);
        baseColor = c;

        outline = DrawableFactory::GetHexagonOutline(pos, Tile::radius, outlineBaseColor);

        borders[0] = TileBorder();
        borders[1] = TileBorder();
        borders[2] = TileBorder();

        // (*outline)[0].position = sf::Vector2f(0, Tile::radius);
        // (*outline)[1].position = sf::Vector2f(Tile::radius * sqrt3div2, Tile::radius * .5f);
        // (*outline)[2].position = sf::Vector2f(Tile::radius * sqrt3div2, Tile::radius * -.5f);
        // (*outline)[3].position = sf::Vector2f(0, Tile::radius * -1);
        // (*outline)[4].position = sf::Vector2f(Tile::radius * sqrt3div2 * -1, Tile::radius * -.5f);
        // (*outline)[5].position = sf::Vector2f(Tile::radius * sqrt3div2 * -1, Tile::radius * .5f);
        // (*outline)[6].position = sf::Vector2f(0, Tile::radius);
    }

    int Tile::GetHeight()
    {
        return height;
    }

    void Tile::UpdateTransforms()
    {
        drawable->setPosition(getPosition());
        float sqrt3div2 = 0.86602540378f;
        EgDrawable *borderDrawable = nullptr;

        borders[0].SetPosition(getPosition() + sf::Vector2f(Tile::radius * sqrt3div2, 0.f));
        borderDrawable = borders[0].GetDrawable();
        borderDrawable->setRotation(borderDrawable->getRotation() + 90.f);

        borders[1].SetPosition(getPosition() + sf::Vector2f((Tile::radius - 5.f) * .5f, (Tile::radius - 5.f) * sqrt3div2));
        borderDrawable = borders[1].GetDrawable();
        borderDrawable->setRotation(borderDrawable->getRotation() + 150.f);

        borders[2].SetPosition(getPosition() + sf::Vector2f((Tile::radius - 5.f) * -.5f, (Tile::radius - 5.f) * sqrt3div2));
        borderDrawable = borders[2].GetDrawable();
        borderDrawable->setRotation(borderDrawable->getRotation() + 30.f);
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

    void Tile::ConcatDrawable(std::unordered_map<int, std::vector<EgDrawable *> *> *res)
    {
        if (IsDrawable())
        {
            PushDrawableToRes(res, drawable);
            auto borderLayer = drawable->GetLayer() + 1;
            if (neighbours[2] != nullptr && neighbours[2]->GetHeight() != height)
            {
                PushDrawableToRes(res, borders[0].GetDrawable(), borderLayer);
            }
            if (neighbours[5] != nullptr && neighbours[5]->GetHeight() != height)
            {
                PushDrawableToRes(res, borders[1].GetDrawable(), borderLayer);
            }
            if (neighbours[4] != nullptr && neighbours[4]->GetHeight() != height)
            {
                PushDrawableToRes(res, borders[2].GetDrawable(), borderLayer);
            }

            if (displayOutline && outlineModified)
            {
                outline->setPosition(getPosition());
                auto map = static_cast<Map *>(parent);

                PushDrawableToRes(res, outline, map->InZoneOfControl(this, 0) ? 2 : outline->GetLayer());
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
        Highlight(sf::Color::White);
    }

    void Tile::Highlight(sf::Color color)
    {
        outline->SetColor(color);
        outline->SetLayer(1);
        outlineModified = true;
    }

    void Tile::Highlight(sf::Color color, int layer)
    {
        Highlight(color);
        outline->SetLayer(layer);
        outlineModified = true;
    }

    void Tile::AlternateHighlight()
    {
        outline->SetColor(sf::Color::Red);
        outline->SetLayer(2);
        outlineModified = true;
    }

    void Tile::ResetHighlight()
    {
        outline->SetColor(outlineBaseColor);
        outline->SetLayer(0);
        outlineModified = false;
    };

    bool Tile::InteractWithEntity(Entity *selected)
    {
        StateManager::GetInstance()->Mystery();
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