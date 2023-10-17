#pragma once

#include "../Drawable/drawable.hpp"
#include "../Drawable/drawablefactory.hpp"
#include "transform.hpp"

namespace egl
{
    class Entity
    {
    protected:
        Transform transform;
        EgDrawable *drawable;

    public:
        Entity();
        virtual void ConcatDrawable(std::vector<EgDrawable *> *res)
        {
            if (IsDrawable())
            {
                res->push_back(drawable);
            }
        };
        Transform *GetTransform() { return &transform; }

        bool IsDrawable();
        virtual void AddDrawable(EgDrawable *drawable);
        void SetPosition(sf::Vector3f pos);
    };
}