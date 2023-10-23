#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"

namespace egl
{
    class Battalion : public Entity
    {
    protected:
        Battalion **bat_ref;

        void ClearBatRef();

    public:
        Battalion(Battalion **bat_ref) : Entity(EntityType::E_Battalion), bat_ref(bat_ref){};
        void AddDrawable();
        bool IsSelectable() override;
        Entity *AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
        void AttachToTile(Battalion **tile_bat_ref);
    };
}
