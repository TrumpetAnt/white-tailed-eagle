#pragma once

#include <vector>

#include "../Entity/entity.hpp"
#include "../../Systems/GameObjects/Factories/EntityFactory.hpp"
#include "../../Systems/GameObjects/Units/ProjectilePool.hpp"
#include "../../Systems/GameObjects/Path/PathSegmentPool.hpp"

namespace egl
{
    class State
    {
    private:
        std::vector<Entity *> *entities = new std::vector<Entity *>();
        std::vector<Entity *> *playerEntities = new std::vector<Entity *>();
        std::vector<Entity *> *npcEntities = new std::vector<Entity *>();

    public:
        State();
        std::vector<Entity *> *GetEntities();
        Entity *SelectAt(float x, float y);

        std::vector<Entity *> *GetPlayerEntities();
        std::vector<Entity *> *GetNpcEntities();

        void NextTurn();

        void Mystery();
    };
}