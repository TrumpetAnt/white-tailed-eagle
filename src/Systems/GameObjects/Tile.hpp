#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/Drawable/drawablefactory.hpp"

namespace egl
{
    class Tile : public Entity
    {
    public:
        void AddDrawable();
    };
}