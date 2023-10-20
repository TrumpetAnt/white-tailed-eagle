#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = new std::vector<Entity *>();
        entities->push_back(EntityFactory::GetMap(20, 10));
    }

    std::vector<Entity *> *State::GetEntities()
    {
        return entities;
    };
}