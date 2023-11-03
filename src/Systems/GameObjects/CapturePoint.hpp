#pragma once

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/TextureManager/texturemanager.hpp"

#include "EntityType.hpp"

namespace egl
{
    class CapturePoint : public Entity
    {
    protected:
        int team;

    public:
        CapturePoint(int team);
        void AddDrawable();

        static constexpr float radius = 15;
    };
}
