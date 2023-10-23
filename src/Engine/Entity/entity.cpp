#include "entity.hpp"

namespace egl
{
    bool Entity::IsDrawable()
    {
        return drawable != nullptr;
    }

    void Entity::AddDrawable(EgDrawable *drawable)
    {
        drawable = drawable;
    }

    EgDrawable *Entity::GetDrawable()
    {
        return drawable;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->setPosition(pos);
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
}