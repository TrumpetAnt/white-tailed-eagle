#include "Npc.hpp"
namespace egl
{
    std::vector<interaction_t> *Npc::GetInteractions(State *state)
    {
        auto res = new std::vector<interaction_t>();
        auto npcBattalions = state->GetNpcEntities();
        for (auto e : *npcBattalions)
        {
            auto bat = static_cast<Battalion *>(e);
            if (bat->IsDead())
            {
                continue;
            }
            auto tile = static_cast<Tile *>(bat->parent);
            auto map = static_cast<Map *>(tile->parent);
            auto pos = tile->GetDiscretePos();
            auto actions = map->GetBattalionActions(pos.x, pos.y, bat->GetMovementPoints(), bat->GetTeam());
            bat->SetActions(actions);
            for (auto action : *actions)
            {
                auto enemy = action.first->GetBattalion();
                if (enemy == nullptr || enemy->GetTeam() == bat->GetTeam())
                {
                    continue;
                }
                res->push_back(interaction_t(e, enemy));
                break;
            }
        }
        // @todo @bug Sleeping bug, if AI plans multiple moves to interact with same enemy and kills on first move
        return res;
    }
}