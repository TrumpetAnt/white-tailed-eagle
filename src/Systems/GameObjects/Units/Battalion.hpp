#pragma once

#include "../../../Engine/Entity/entity.hpp"

namespace egl
{
    class Battalion : public Entity
    {
    public:
        void AddDrawable();
        bool IsSelectable() override;
        bool AttemptSelect(float x, float y) override;
        void Highlight() override;
        void ResetHighlight() override;
    };
}
