#include "statemanager.hpp"

namespace egl
{
    StateManager::StateManager()
    {
        state = new State();
    }

    std::vector<Drawable *> *StateManager::GetDrawables()
    {
        auto res = new std::vector<Drawable *>();
        auto entities = state->GetEntities();
        for (auto entity : entities)
        {
            if (entity->IsDrawable())
            {
                res->push_back(entity->GetDrawable());
            }
        }

        return res;
    }
}