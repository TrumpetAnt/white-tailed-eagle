#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../Map.hpp"

namespace egl
{
    class EntityBuilder
    {
    private:
        Entity *entity;

    public:
        EntityBuilder()
        {
            entity = new Entity();
        };

        EntityBuilder *AddDrawable()
        {
            return this;
        }

        EntityBuilder *AtPosition(float x, float y)
        {
            entity->SetPosition(sf::Vector2f(x, y));
            return this;
        }

        Entity *Build()
        {
            return entity;
        }
    };
}