#pragma once

#include "../Drawable/drawable.hpp"
#include "../Drawable/drawablefactory.hpp"

namespace egl
{
    class Entity : public sf::Transformable
    {
    protected:
        EgDrawable *drawable = nullptr;

    public:
        virtual void ConcatDrawable(std::vector<EgDrawable *> *res)
        {
            if (IsDrawable())
            {
                res->push_back(drawable);
            }
        };

        virtual bool IsDrawable();
        virtual void AddDrawable(EgDrawable *drawable);
        EgDrawable *GetDrawable();
        void SetPosition(sf::Vector2f pos);
    };
}