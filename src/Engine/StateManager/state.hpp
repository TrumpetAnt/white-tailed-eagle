#pragma once

#include <vector>

#include "../Entity/entity.hpp"
#include "../Entity/entityfactory.hpp"

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