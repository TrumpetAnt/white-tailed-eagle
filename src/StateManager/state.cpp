#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = std::vector<Entity *>();
        entities.push_back(EntityFactory::GetTriangle(50, 50));
        entities.push_back(EntityFactory::GetTriangle(150, 150));
        entities.push_back(EntityFactory::GetTriangle(250, 250));
    }

    std::vector<Entity *> State::GetEntities()
    {
        return entities;
    };
}