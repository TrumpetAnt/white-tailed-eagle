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
        float initialHp = 100.f;
        float hitPoints = initialHp;
        float maxDamage = 50.f;
        HealthBar *healthBar;

    public:
        Battalion() : Entity(EntityType::E_Battalion){};
        void UpdateTransforms() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;
        void AddDrawable();
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
        uint GetMovementPoints();
        Tile *GetParentTile();
        bool InteractWithEntity(Entity *e) override;
        void Damage(float damage);
    };
}
