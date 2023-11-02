#pragma once

#include <vector>

#include "../../Engine/Entity/entity.hpp"
#include "../../Engine/StateManager/state.hpp"

namespace egl
{
    typedef std::pair<Entity *, Entity *> interaction_t;
    class Npc
    {
    public:
        std::vector<interaction_t> *GetInteractions(State *state);
    };
}
