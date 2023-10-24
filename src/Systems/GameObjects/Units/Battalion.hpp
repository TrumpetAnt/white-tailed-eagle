#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "HealthBar.hpp"

namespace egl
{
    class Tile;
    class Map;
    class Battalion : public Entity
    {
    protected:
        uint movementPoints = 2;
        uint availablePoints = movementPoints;
        float initialHp = 100.f;
        float hitPoints = initialHp;
        float maxDamage = 50.f;
        HealthBar *healthBar;
        int team;

    public:
        Battalion(int team) : Entity(EntityType::E_Battalion), team(team){};
        // ~~ Base ~~
        Tile *GetParentTile();
        void NextTurn() override;
        // ~~ Render shit ~~
        void UpdateTransforms() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
        void AddDrawable();
        // ~~ Select ~~
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void MarkAsSpent();
        void ResetHighlight() override;
        // ~~ Movement ~~
        uint GetMovementPoints();
        void SpendMovementPoints(uint cost);
        // ~~ Interact ~~
        bool InteractWithEntity(Entity *e) override;
        void Damage(float damage);
    };
}
