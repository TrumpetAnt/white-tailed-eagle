#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"

namespace egl
{
    class Tile;
    class Map;
    class Battalion : public Entity
    {
    protected:
        uint movementPoints = 2;

    public:
        Battalion() : Entity(EntityType::E_Battalion){};
        void AddDrawable();
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
        uint GetMovementPoints();
    };
}
