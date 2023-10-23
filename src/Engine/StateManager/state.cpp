#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = new std::vector<Entity *>();
        // entities->push_back(EntityFactory::GetMap(1, 1));
        std::vector<Tile *> *out_tiles;
        auto map = EntityFactory::GetMap(25, 11, &out_tiles);
        auto bat = EntityFactory::GetBattalion();
        map->AddBattalionAt(bat, 13, 3);
        entities->push_back(map);
        for (auto tile : *out_tiles)
        {
            entities->push_back(tile);
        }
        entities->push_back(bat);
    }

    std::vector<Entity *> *State::GetEntities()
    {
        return entities;
    };

    Entity *State::SelectAt(float x, float y)
    {
        for (auto entity : *entities)
        {
            if (entity->IsSelectable())
            {
                auto e = entity->AttemptSelect(x, y);
                if (e != nullptr)
                {
                    return e;
                }
            }
        }
        return nullptr;
    }
}