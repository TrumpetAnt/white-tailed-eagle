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

    void Entity::AddDrawable(EgDrawable *drawable)
    {
        drawable = drawable;
    }

    void Entity::SetPosition(sf::Vector3f pos)
    {
        transform.SetPosition(pos);
    }

}