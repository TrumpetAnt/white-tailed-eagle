#include "statemanager.hpp"

namespace egl
{
    StateManager::StateManager()
    {
        state = new State();
    }

    std::vector<EgDrawable *> *StateManager::GetDrawables()
    {
        auto res = new std::vector<EgDrawable *>();
        auto entities = state->GetEntities();
        for (auto entity : *entities)
        {
            if (entity->IsDrawable())
            {
                entity->ConcatDrawable(res);
            }
        }

        return res;
    }
}