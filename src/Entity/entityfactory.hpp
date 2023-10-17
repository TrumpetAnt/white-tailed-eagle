#pragma once

#include "entity.hpp"
#include "entitybuilder.hpp"

namespace egl
{
    class EntityFactory
    {
    private:
        static Entity *GetTriangleBase(float x, float y);

    public:
        static Entity *GetTriangle();
        static Entity *GetTriangle(float x, float y);
    };
}