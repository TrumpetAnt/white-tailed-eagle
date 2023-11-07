#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "HealthBar.hpp"
#include "ProjectilePool.hpp"
#include "../Typedefs.hpp"

namespace egl
{
    class Tile;
    class Map;
    class Battalion : public Entity
    {
    protected:
        int zoneOfControlRadius = 1;
        uint movementPoints = 3;
        uint availablePoints = movementPoints;
        float initialHp = 100.f;
        float hitPoints = initialHp;
        float baseDamage = 20.f;
        float linearDamageVariant = 10.f;
        HealthBar *healthBar;
        int team;
        std::vector<action_t> *actions = nullptr;

        void CleanUpActions();

    public:
        Battalion(int team) : Entity(EntityType::E_Battalion), team(team){};
        // ~~ Base ~~
        Tile *GetParentTile();
        bool MarkedForDestruction() override;
        // ~~ Render shit ~~
        void UpdateTransforms() override;
        void ConcatDrawable(std::unordered_map<int, std::vector<EgDrawable *> *> *res) override;
        void AddDrawable();
        void Hover() override;
        void StopHover() override;
        // ~~ Select ~~
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void MarkAsSpent();
        void ResetHighlight() override;
        std::vector<action_t> *GetPossibleActions();
        action_t ActionToTile(Tile *tile);
        void SetActions(std::vector<action_t> *a);
        // ~~ Movement ~~
        uint GetMovementPoints();
        void SpendMovementPoints(uint cost);
        // ~~ Zone of control
        int GetZoneOfControlRadius();
        // ~~ Interact ~~
        bool InteractWithEntity(Entity *e) override;
        void Damage(float damage);
        void NextTurn() override;
        int GetTeam();
        bool IsDead();

        static constexpr float radius = 25;
    };
}
