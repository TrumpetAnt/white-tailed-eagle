#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = std::vector<Entity *>();
        entities.push_back((Entity *)EntityFactory::GetMap(10, 10));
    }

    std::vector<Entity *> State::GetEntities()
    {
        return entities;
    };
}