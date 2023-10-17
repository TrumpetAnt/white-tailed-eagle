#include "entity.hpp"

namespace egl
{
    Entity::Entity()
    {
        transform = Transform();
    }

    bool Entity::IsDrawable()
    {
        return drawable != nullptr;
    }

    Drawable *Entity::GetDrawable()
    {
        return drawable;
    }

    void Entity::AddDrawable()
    {
        drawable = new Drawable(&transform);
    }

    void Entity::SetPosition(sf::Vector3f pos)
    {
        transform.SetPosition(pos);
    }
}