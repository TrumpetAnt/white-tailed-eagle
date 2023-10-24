#include "state.hpp"

namespace egl
{
    State::State()
    {
        entities = new std::vector<Entity *>();
        // entities->push_back(EntityFactory::GetMap(1, 1));
        std::vector<Tile *> *out_tiles;
        auto map = EntityFactory::GetMap(25, 11, &out_tiles);
        auto bat = EntityFactory::GetBattalion(0);
        auto bat2 = EntityFactory::GetBattalion(0);
        auto bat3 = EntityFactory::GetBattalion(1);
        map->AddBattalionAt(bat, 13, 3);
        map->AddBattalionAt(bat2, 14, 3);
        map->AddBattalionAt(bat3, 14, 4);
        entities->push_back(map);
        for (auto tile : *out_tiles)
        {
            entities->push_back(tile);
        }
        entities->push_back(bat);
        entities->push_back(bat2);
        entities->push_back(bat3);
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