#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "../../../Engine/Drawable/drawablefactory.hpp"
#include "../Tile/Tile.hpp"
#include "../TransformUtils.hpp"

namespace egl
{
    class PathSegment : public Entity
    {
    protected:
        bool hidden = true;

    public:
        PathSegment();
        bool IsDrawable() override;
        void Hide();
        void Show(sf::Vector2f from, sf::Vector2f to, bool angry);
    };
}
