#include "Battalion.hpp"
#include "../Map.hpp"
#include "../Tile.hpp"

namespace egl
{
    sf::Color TeamToColor(int team)
    {
        switch (team)
        {
        case 0:
            return sf::Color::Red;
        case 1:
            return sf::Color::Blue;
        default:
            return sf::Color::Black;
        }
    };
    bool Battalion::MarkedForDestruction()
    {
        return IsDead();
    };

    void Battalion::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetCircle(pos, Battalion::radius);

        drawable->SetColor(TeamToColor(team));

        healthBar = new HealthBar(initialHp, DrawableFactory::GetHealthBar(60.f, 20.f));
    }

    void Battalion::UpdateTransforms()
    {
        drawable->setPosition(getPosition());
        healthBar->setPosition(getPosition() + sf::Vector2f(0.f, 30.f));
    }

    void Battalion::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        if (MarkedForDestruction())
        {
            return;
        }
        res->push_back(drawable);
        if (hitPoints < initialHp)
        {
            res->push_back(healthBar);
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
        auto actions = m->GetBattalionActions(pos.x, pos.y, GetMovementPoints());
        auto tiles = new std::vector<Tile *>();
        for (auto action : *actions)
        {
            tiles->push_back(action.first);
            delete action.second;
        }
        m->HighlightTiles(tiles);
        delete tiles;
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
    }

    uint Battalion::GetMovementPoints()
    {
        return availablePoints;
    }

    void Battalion::SpendMovementPoints(uint cost)
    {
        availablePoints = cost >= availablePoints ? 0 : availablePoints - cost;
    }

    Tile *Battalion::GetParentTile()
    {
        return static_cast<Tile *>(parent);
    }

    void Battalion::NextTurn()
    {
        availablePoints = movementPoints;
        drawable->SetColor(TeamToColor(team));
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

    bool Battalion::InteractWithEntity(Entity *e)
    {
        switch (e->GetEntityType())
        {
        case EntityType::E_Battalion:
            auto diff = getPosition() - e->getPosition();
            auto dist = diff.x * diff.x + diff.y * diff.y;
            auto tile_width = Tile::radius * Tile::radius * 4;
            if (dist < tile_width * movementPoints * movementPoints)
            {
                auto other_bat = static_cast<Battalion *>(e);
                if (other_bat->team != team)
                {
                    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                    Damage(r * linearDamageVariant + baseDamage);
                    other_bat->SpendMovementPoints(other_bat->GetMovementPoints());
                    other_bat->MarkAsSpent();
                    for (int i = 0; i < 5; i++)
                    {
                        auto offset_start = randomOffset(Battalion::radius / 4.f);
                        auto offset_end = randomOffset(Battalion::radius);
                        ProjectilePool::GetInstance()->Shoot(other_bat->getPosition() + offset_start, getPosition() + offset_end, 30);
                    }

                    return true;
                }
            }
            break;
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
        if (tile != nullptr)
        {
            tile->ClearBattalion();
        }
    }

    bool Battalion::IsDead()
    {
        return hitPoints <= 0.f;
    }
}
