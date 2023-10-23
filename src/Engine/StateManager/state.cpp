#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = new std::vector<Entity *>();
        // entities->push_back(EntityFactory::GetMap(1, 1));
        auto map = EntityFactory::GetMap(25, 11);
        map->AddBattalionAt(EntityFactory::GetBattalion(), 13, 3);
        entities->push_back(map);
    }

    std::vector<Entity *> *State::GetEntities()
    {
        return entities;
    };
}