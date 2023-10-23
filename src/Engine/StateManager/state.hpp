#pragma once

#include <vector>

#include "../Entity/entity.hpp"
#include "../../Systems/GameObjects/Builders/entityfactory.hpp"

namespace egl
{
    class State
    {
    private:
        std::vector<Entity *> *entities;

    public:
        State();
        std::vector<Entity *> *GetEntities();
    };
}