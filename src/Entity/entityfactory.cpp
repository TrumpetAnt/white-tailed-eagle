#include "entityfactory.hpp"

namespace egl
{
    Entity *EntityFactory::GetTriangleBase(float x, float y)
    {
        return EntityBuilder().AddDrawable()->AtPosition(x, y)->Build();
    };

    Entity *EntityFactory::GetTriangle()
    {
        return EntityFactory::GetTriangleBase(100, 100);
    }

    Entity *EntityFactory::GetTriangle(float x, float y)
    {
        return EntityFactory::GetTriangleBase(x, y);
    }
}