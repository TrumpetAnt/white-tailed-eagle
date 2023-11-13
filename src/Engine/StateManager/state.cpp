#include "state.hpp"

namespace egl
{
    State::State()
    {
        // entities->push_back(EntityFactory::GetMap(1, 1));
        std::vector<Tile *> *out_tiles;
        auto map = EntityFactory::GetMap(19, 12, &out_tiles);
        auto bat = EntityFactory::GetBattalion(0);
        auto bat2 = EntityFactory::GetBattalion(0);
        auto bat3 = EntityFactory::GetBattalion(1);
        auto bat4 = EntityFactory::GetBattalion(1);
        map->AddBattalionAt(bat, 11, 3);
        map->AddBattalionAt(bat2, 12, 3);
        map->AddBattalionAt(bat3, 14, 4);
        map->AddBattalionAt(bat4, 14, 5);
        entities->push_back(map);
        for (auto tile : *out_tiles)
        {
            entities->push_back(tile);
        }
        entities->push_back(bat);
        entities->push_back(bat2);
        playerEntities->push_back(bat);
        playerEntities->push_back(bat2);
        npcEntities->push_back(bat3);
        npcEntities->push_back(bat4);
        entities->push_back(bat3);
        entities->push_back(bat4);

        auto cp2 = EntityFactory::GetCapturePoint(1);

        map->AddCapturePointAt(cp2, 16, 5);
        entities->push_back(cp2);

        entities->push_back(EntityFactory::GetNoiseMap());

        ProjectilePool::GetInstance()
            ->TrackEntities(entities);
        PathSegmentPool::GetInstance()
            ->TrackEntities(entities);
    }

    std::vector<Entity *> *State::GetEntities()
    {
        return entities;
    };

    std::vector<Entity *> *State::GetPlayerEntities()
    {
        return playerEntities;
    }

    std::vector<Entity *> *State::GetNpcEntities()
    {
        return npcEntities;
    }

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

    void State::NextTurn()
    {
        for (auto entity : *entities)
        {
            entity->NextTurn();
        }
    }

    void State::Mystery()
    {
        for (auto e : *entities)
        {
            if (e->GetEntityType() != EntityType::E_Tile)
            {
                continue;
            }
            auto tile = static_cast<Tile *>(e);
            if (tile->GetBattalion() != nullptr)
            {
                std::cout << "Tile ("
                          << tile->GetDiscretePos().x
                          << ","
                          << tile->GetDiscretePos().y
                          << ") is occipied"
                          << std::endl;
            }
        }
    }
}