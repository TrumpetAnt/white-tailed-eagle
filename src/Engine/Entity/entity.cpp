#include "entity.hpp"

namespace egl
{
    Entity::Entity(uint entityType) : entityType(entityType){};

    Entity::Entity(uint entityType, Entity *parent) : entityType(entityType), parent(parent)
    {
        if (parent != nullptr)
        {
            parent->AttachChild(this);
        }
    };

    bool Entity::IsDrawable()
    {
        return drawable != nullptr;
    }

    void Entity::AddDrawable(EgDrawable *drawable)
    {
        this->drawable = drawable;
    }

    EgDrawable *Entity::GetDrawable()
    {
        return drawable;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        setPosition(pos);
        UpdateTransforms();
    }

    uint Entity::GetEntityType()
    {
        return entityType;
    }

    bool Entity::IsSelectable()
    {
        return false;
    }

    Entity *Entity::AttemptSelect(float x, float y)
    {
        return nullptr;
    }

    void Entity::AttachChild(Entity *child)
    {
        children->push_back(child);
        child->parent = this;
    }

    void Entity::DetachChild(Entity *child)
    {
        auto c = children->begin();
        for (; c != children->end(); c++)
        {
            if (*c == child)
            {
                break;
            }
        }
        if (c != children->end())
        {
            (*c)->parent = nullptr;
            children->erase(c);
        }
    }

    void Entity::DetachFromParent()
    {
        if (parent == nullptr)
        {
            return;
        }
        parent->DetachChild(this);
    }

    void Entity::PushDrawableToRes(std::unordered_map<int, std::vector<EgDrawable *> *> *res, EgDrawable *drawable)
    {
        auto layer = drawable->GetLayer();
        PushDrawableToRes(res, drawable, drawable->GetLayer());
    }

    void Entity::PushDrawableToRes(std::unordered_map<int, std::vector<EgDrawable *> *> *res, EgDrawable *drawable, int layer)
    {
        if (res->count(layer) == 0)
        {
            res->insert({layer, new std::vector<EgDrawable *>()});
        }
        auto vec = res->at(layer);
        vec->push_back(drawable);
    }
}