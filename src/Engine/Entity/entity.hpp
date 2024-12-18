#pragma once

#include <unordered_map>
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

        void PushDrawableToRes(std::unordered_map<int, std::vector<EgDrawable *> *> *res, EgDrawable *drawable);
        void PushDrawableToRes(std::unordered_map<int, std::vector<EgDrawable *> *> *res, EgDrawable *drawable, int layer);

    public:
        Entity *parent = nullptr;

        Entity(uint entityType);
        Entity(uint entityType, Entity *parent);
        virtual bool MarkedForDestruction() { return false; } // @Todo Utilize for object destruction, probably use with ObjectPool though...
        virtual void UpdateTransforms()
        {
            if (drawable != nullptr)
            {
                drawable->setPosition(getPosition());
            }
        }
        virtual void ConcatDrawable(std::unordered_map<int, std::vector<EgDrawable *> *> *res)
        {
            if (IsDrawable())
            {
                PushDrawableToRes(res, drawable);
            }
        };

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
        virtual void Hover(){};
        virtual void StopHover(){};

        virtual bool InteractWithEntity(Entity *e) { return false; };
        virtual void NextTurn(){};
    };
}