#pragma once

#include "../Drawable/drawable.hpp"
#include "../Drawable/drawablefactory.hpp"

namespace egl
{
    class Entity : public sf::Transformable
    {
    protected:
        EgDrawable *drawable = nullptr;
        uint entityType;
        std::vector<Entity *> *children = new std::vector<Entity *>();

    public:
        Entity *parent = nullptr;

        Entity(uint entityType);
        Entity(uint entityType, Entity *parent);
        virtual void UpdateTransforms()
        {
            if (drawable != nullptr)
            {
                drawable->setPosition(getPosition());
            }
        }
        virtual void ConcatDrawable(std::vector<EgDrawable *> *res)
        {
            if (IsDrawable())
            {
                res->push_back(drawable);
            }
        };
        virtual void NextTurn(){};

        virtual bool IsDrawable();
        virtual void AddDrawable(EgDrawable *drawable);
        EgDrawable *GetDrawable();
        void SetPosition(sf::Vector2f pos);
        uint GetEntityType();

        void AttachChild(Entity *child);
        void DetachChild(Entity *child);
        void DetachFromParent();

        virtual bool IsSelectable();
        virtual Entity *AttemptSelect(float x, float y);
        virtual void Highlight(){};
        virtual void ResetHighlight(){};

        virtual bool InteractWithEntity(Entity *e) { return false; };
    };
}