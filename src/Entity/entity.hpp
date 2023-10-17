#pragma once

#include "../Drawable/drawable.hpp"
#include "transform.hpp"

namespace egl
{
    class Entity
    {
    private:
        Drawable *drawable;
        Transform transform;

    public:
        Entity();
        bool IsDrawable();
        Drawable *GetDrawable();
        void AddDrawable();
        void SetPosition(sf::Vector3f pos);
    };
}