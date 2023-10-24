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
    }

    void Battalion::AddDrawable()
    {
        auto pos = this->getPosition();
        drawable = DrawableFactory::GetCircle(pos);

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
        res->push_back(drawable);
        if (hitPoints < initialHp)
        {
            res->push_back(healthBar);
        }
    }

    bool Battalion::IsSelectable()
    {
        return true;
    }

    Entity *Battalion::AttemptSelect(float x, float y)
    {
        auto distance = getPosition() - sf::Vector2f(x, y);
        return distance.x * distance.x + distance.y * distance.y < 25.f * 25.f ? this : nullptr;
    }

    void Battalion::Highlight()
    {
        drawable->SetColor(sf::Color::White);
        auto tile = static_cast<Tile *>(parent);
        auto m = static_cast<Map *>(tile->parent);
        auto pos = tile->GetDiscretePos();
        m->HighlightTilesAround(pos.x, pos.y, GetMovementPoints());
    }

    void Battalion::ResetHighlight()
    {
        drawable->SetColor(TeamToColor(team));
        auto m = static_cast<Map *>(parent->parent);
        m->ResetAllHighlightedTiles();
    }

    uint Battalion::GetMovementPoints()
    {
        return movementPoints;
    }

    Tile *Battalion::GetParentTile()
    {
        return static_cast<Tile *>(parent);
    }

    bool Battalion::InteractWithEntity(Entity *e)
    {
        switch (e->GetEntityType())
        {
        case EntityType::E_Battalion:
            auto diff = getPosition() - e->getPosition();
            if (diff.x * diff.x + diff.y * diff.y < Tile::radius * Tile::radius * 4 * movementPoints * movementPoints)
            {
                auto bat = static_cast<Battalion *>(e);
                if (bat->team != team)
                {
                    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                    Damage(r * maxDamage);
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
    }
}
