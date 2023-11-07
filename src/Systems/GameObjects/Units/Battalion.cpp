#include "Battalion.hpp"
#include "../Map.hpp"
#include "../Tile.hpp"

namespace egl
{
    sf::Color TeamToColor(int team)
    {
        return sf::Color::White;
    };

    void Battalion::CleanUpActions()
    {
        if (actions == nullptr)
        {
            return;
        }
        for (auto action : *actions)
        {
            delete action.second;
        }
        delete actions;
        actions = nullptr;
    }

    bool Battalion::MarkedForDestruction()
    {
        return IsDead();
    };

    sf::Texture *TeamToTexture(int team)
    {
        auto tm = TextureManager::GetInstance();
        switch (team)
        {
        case 0:
            return tm->LoadTexture("assets/img/TinyBattleAssetPack/tile_0160.png");
        case 1:
            return tm->LoadTexture("assets/img/TinyBattleAssetPack/tile_0142.png");
        default:
            throw std::invalid_argument("Unhandled switch case");
        }
    }

    void Battalion::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetRectangle(sf::Vector2f(30, 30), sf::Vector2f(16, 16));
        drawable->SetTexture(TeamToTexture(team));
        drawable->SetColor(TeamToColor(team));
        healthBar = new HealthBar(initialHp, DrawableFactory::GetHealthBar(60.f, 20.f));
        UpdateTransforms();
    }

    void Battalion::Hover()
    {
        parent->Hover();
    };

    void Battalion::StopHover()
    {
        if (parent)
        {
            parent->StopHover();
        }
    };

    void Battalion::UpdateTransforms()
    {
        drawable->setPosition(getPosition());
        healthBar->setPosition(getPosition() + sf::Vector2f(0.f, 30.f));
    }

    void Battalion::ConcatDrawable(std::unordered_map<int, std::vector<EgDrawable *> *> *res)
    {
        if (MarkedForDestruction())
        {
            return;
        }
        PushDrawableToRes(res, drawable);
        if (hitPoints < initialHp)
        {
            PushDrawableToRes(res, healthBar);
        }
    }

    bool Battalion::IsSelectable()
    {
        return 0 < availablePoints && team == 0;
    }

    Entity *Battalion::AttemptSelect(float x, float y)
    {
        auto distance = getPosition() - sf::Vector2f(x, y);
        return distance.x * distance.x + distance.y * distance.y < Battalion::radius * Battalion::radius ? this : nullptr;
    }

    void Battalion::Highlight()
    {
        drawable->SetColor(TeamToColor(team) + sf::Color(75, 75, 75));
        auto tile = static_cast<Tile *>(parent);
        auto m = static_cast<Map *>(tile->parent);
        auto pos = tile->GetDiscretePos();
        actions = m->GetBattalionActions(pos.x, pos.y, GetMovementPoints(), team);
        m->HighlightActions(actions);
        tile->Highlight(sf::Color::Black, 3);
    }

    void Battalion::MarkAsSpent()
    {
        drawable->SetColor(TeamToColor(team) - sf::Color(75, 75, 75, 0));
    }

    void Battalion::ResetHighlight()
    {
        if (IsSelectable())
        {
            drawable->SetColor(TeamToColor(team));
        }
        else
        {
            MarkAsSpent();
        }

        auto m = static_cast<Map *>(parent->parent);
        m->ResetAllHighlightedTiles();
        PathSegmentPool::GetInstance()->UnMarkPath();
    }

    std::vector<action_t> *Battalion::GetPossibleActions()
    {
        return actions;
    }

    action_t Battalion::ActionToTile(Tile *tile)
    {
        if (actions == nullptr || actions->size() == 0)
        {
            return action_t(nullptr, nullptr);
        }

        for (auto action : *actions)
        {
            if (action.first == tile)
            {
                return action;
            }
        }
        return action_t(nullptr, nullptr);
    }

    void Battalion::SetActions(std::vector<action_t> *a)
    {
        CleanUpActions();
        actions = a;
    }

    uint Battalion::GetMovementPoints()
    {
        return availablePoints;
    }

    void Battalion::SpendMovementPoints(uint cost)
    {
        availablePoints = cost >= availablePoints ? 0 : availablePoints - cost;
    }

    int Battalion::GetZoneOfControlRadius()
    {
        return zoneOfControlRadius;
    }

    Tile *Battalion::GetParentTile()
    {
        return static_cast<Tile *>(parent);
    }

    void Battalion::NextTurn()
    {
        availablePoints = movementPoints;
        drawable->SetColor(TeamToColor(team));
        CleanUpActions();
    };

    int Battalion::GetTeam()
    {
        return team;
    }

    sf::Vector2f randomOffset(float radius)
    {
        float r_x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float r_y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        return sf::Vector2f(0.5f - r_x, 0.5f - r_y) * radius * 2.f;
    }

    bool Battalion::InteractWithEntity(Entity *selected)
    {
        switch (selected->GetEntityType())
        {
        case EntityType::E_Battalion:
            auto selected_bat = static_cast<Battalion *>(selected);
            if (selected_bat->team == team)
            {
                break;
            }
            auto tile = static_cast<Tile *>(parent);
            auto map = static_cast<Map *>(tile->parent);
            auto action = selected_bat->ActionToTile(tile);
            if (action.first == nullptr)
            {
                break;
            }
            auto tiles = action.second;
            auto second_to_last = tiles->at(1);
            if (tiles->size() > 2 && second_to_last != selected->parent)
            {
                if (second_to_last->GetBattalion() != nullptr)
                {
                    break;
                }
                if (!map->AttemptMoveBattalionToTile(selected_bat, second_to_last))
                {
                    std::cout << "What the frickin heck??" << std::endl;
                }
            }

            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            Damage(r * linearDamageVariant + baseDamage);
            selected_bat->SpendMovementPoints(selected_bat->GetMovementPoints());
            selected_bat->MarkAsSpent();
            for (int i = 0; i < 5; i++)
            {
                auto offset_start = randomOffset(Battalion::radius / 4.f);
                auto offset_end = randomOffset(Battalion::radius);
                ProjectilePool::GetInstance()->Shoot(selected_bat->getPosition() + offset_start, getPosition() + offset_end, 30);
            }

            PathSegmentPool::GetInstance()->UnMarkPath();
            return true;
        }
        return false;
    }

    void Battalion::Damage(float damage)
    {
        std::cout << "Ouch for " << damage << " healthpoints" << std::endl;
        hitPoints -= damage;
        healthBar->AlterHp(-1 * damage);
        if (!IsDead())
        {
            return;
        }

        auto tile = static_cast<Tile *>(parent);
        auto map = static_cast<Map *>(tile->parent);
        map->RemoveZoneOfControlFromBattalion(this);
        tile->ClearBattalion();
    }

    bool Battalion::IsDead()
    {
        return hitPoints <= 0.f;
    }
}
