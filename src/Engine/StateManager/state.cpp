#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = new std::vector<Entity *>();
        // entities->push_back(EntityFactory::GetMap(1, 1));
        entities->push_back(EntityFactory::GetMap(25, 11));
    }

    std::vector<Entity *> *State::GetEntities()
    {
        return entities;
    };
}