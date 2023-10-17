#pragma once

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

namespace egl
{
    class DrawableFactory
    {
    public:
        static EgDrawable *GetTriangle(Transform *transform);
        static EgDrawable *GetHexagon(Transform *transform);
    };
}
