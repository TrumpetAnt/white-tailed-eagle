#include "Map.hpp"
#include "../../Engine/StateManager/statemanager.hpp"

namespace egl
{
    Map::Map(int width, int height, std::vector<Tile *> *tiles) : width(width), height(height), tiles(tiles), Entity(EntityType::E_Map)
    {
        if (width <= 0 || height <= 0 || 1000000 < width * height || tiles == nullptr || tiles->size() != width * height)
        {
            throw std::invalid_argument("Map requires width and height > 0 and width * height < 1000001");
        }
        for (auto tile : *tiles)
        {
            this->AttachChild(tile);
        }
    };

    bool Map::checkBounds(int x, int y)
    {
        return 0 <= x && 0 <= y && x <= width && y <= height;
    }

    bool Map::IsDrawable()
    {
        return true;
    }

    void Map::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        for (auto tile : *tiles)
        {
            tile->ConcatDrawable(res);
        }
    }

    void Map::AddBattalionAt(Battalion *bat, int x, int y)
    {
        if (!checkBounds(x, y))
        {
            return;
        }
        auto tile = tiles->at(y * width + x);
        tile->AddBattalion(bat);
        bat->setPosition(tile->getPosition());
        bat->UpdateTransforms();
    }

    void Map::AddCapturePointAt(CapturePoint *cp, int x, int y)
    {
        if (!checkBounds(x, y))
        {
            return;
        }
        auto tile = tiles->at(y * width + x);
        tile->AttachChild(cp);
        cp->setPosition(tile->getPosition());
        cp->UpdateTransforms();
    }

    std::vector<Tile *> *Map::GetTileSurroundings(Tile *target, int radius)
    {
        auto res = new std::vector<Tile *>();
        auto pos = target->GetDiscretePos();
        auto r2 = radius * radius * Tile::radius * Tile::radius * 4;

        for (int row = std::max(pos.y - radius, 0); row < pos.y + radius + 1 && row < height; row++)
        {
            for (int col = std::max(pos.x - radius, 0); col < pos.x + radius + 1 && col < width; col++)
            {
                auto tile = tiles->at(row * width + col);
                if (target->SqrDistanceToTile(*tile) < r2)
                {
                    res->push_back(tile);
                }
            }
        }

        return res;
    }

    void Map::HighlightTile(Tile *tile)
    {
        auto b = tile->GetBattalion();
        if (b != nullptr && b->GetTeam() != 0)
        {
            tile->AlternateHighlight();
        }
        else
        {
            tile->Highlight();
        }

        highlightedTiles->push_back(tile);
    }

    void Map::HighlightTilesAround(int x, int y, int r)
    {
        if (!checkBounds(x, y))
        {
            return;
        }

        auto surroundings = GetTileSurroundings(tiles->at(x + width * y), r);
        for (auto tile : *surroundings)
        {
            HighlightTile(tile);
        }
        delete surroundings;
    }

    void Map::HighlightTiles(std::vector<Tile *> *tiles)
    {
        for (auto tile : *tiles)
        {
            HighlightTile(tile);
        }
    }

    void Map::HighlightActions(std::vector<action_t> *actions)
    {
        for (auto action : *actions)
        {
            HighlightTile(action.first);
        }
    }

    void Map::ResetAllHighlightedTiles()
    {
        for (auto tile : *highlightedTiles)
        {
            tile->ResetHighlight();
        }
        highlightedTiles->clear();
    }

    bool Map::AttemptMoveBattalionToTile(Battalion *bat, Tile *tile)
    {
        auto cost = CostToTile(bat->ActionToTile(tile).second);
        if (cost < 0.f)
        {
            return false;
        }
        bat->SpendMovementPoints(cost);
        tile->AddBattalion(bat);
        return true;
        return false;
    }

    void Map::GetTileNeighbours(std::vector<Tile *> *out_vec, Tile *target)
    {
        out_vec->clear();
        auto pos = target->GetDiscretePos();
        auto x_offset = pos.y % 2;
        sf::Vector2i delta[6] = {sf::Vector2i(-1 + x_offset, -1),
                                 sf::Vector2i(0 + x_offset, -1),
                                 sf::Vector2i(1, 0),
                                 sf::Vector2i(-1, 0),
                                 sf::Vector2i(-1 + x_offset, 1),
                                 sf::Vector2i(0 + x_offset, 1)};
        for (int i = 0; i < 6; i++)
        {
            auto n_pos = delta[i] + pos;
            if (checkBounds(n_pos.x, n_pos.y))
            {
                out_vec->push_back(tiles->at(PosToIndex(n_pos)));
            }
        }
    }

    int Map::PosToIndex(sf::Vector2i pos)
    {
        return pos.x + pos.y * width;
    }

    float Heuristic(sf::Vector2i pos, sf::Vector2i target)
    {
        auto diff = target - pos;
        return static_cast<float>(diff.x * diff.x) + static_cast<float>(diff.y * diff.y);
    }

    std::vector<Tile *> *Map::FindPaths(Tile *source, sf::Vector2i target, int movementPoints)
    {
        auto res = new std::vector<Tile *>();
        ExploreNode goal = {nullptr, 0.f, 0.f, -1};

        auto neighbours = std::vector<Tile *>();
        auto explored = std::unordered_map<int, ExploreNode>();
        auto frontier = MinHeap(tiles->size());

        frontier.insertKey(ExploreNode{source, 0.f, 0.f, PosToIndex(source->GetDiscretePos())});

        auto moveCost = 1;

        while (!frontier.isEmpty())
        {
            auto explore_node = frontier.extractMin();
            auto explore_pos_i = PosToIndex(explore_node.tile->GetDiscretePos());
            explored.insert({explore_pos_i, explore_node});

            if (explore_node.tile->GetDiscretePos() == target)
            {
                goal = explore_node;
                break;
            }

            GetTileNeighbours(&neighbours, explore_node.tile);
            for (auto neighbour : neighbours)
            {
                auto neighbour_pos = neighbour->GetDiscretePos();
                auto next_cost = explore_node.cost + moveCost;
                if (explored.count(PosToIndex(neighbour_pos)) == 0 && movementPoints <= next_cost)
                {
                    frontier.insertKey(ExploreNode{neighbour, next_cost + Heuristic(neighbour_pos, target), next_cost, explore_pos_i});
                }
            }
        }
        ExploreNode current = goal;
        if (current.tile != nullptr)
        {
            while (current.prev_i >= 0 && res->size() < 1000)
            {
                res->push_back(current.tile);
                current = explored.at(current.prev_i);
            }
        }
        return res;
    }

    std::vector<action_t> *Map::GetBattalionActions(int x, int y, int movementPoints, int team)
    {
        auto res = new std::vector<action_t>();
        auto neighbours = std::vector<Tile *>();
        auto explored = std::unordered_map<int, ExploreNode>();
        auto frontier = MinHeap(tiles->size());

        auto source = tiles->at(x + y * width);
        frontier.insertKey(ExploreNode{source, 0.f, static_cast<float>(movementPoints), PosToIndex(source->GetDiscretePos())});

        while (!frontier.isEmpty())
        {
            auto explore_node = frontier.extractMin();
            auto explore_pos_i = PosToIndex(explore_node.tile->GetDiscretePos());
            explored.insert({explore_pos_i, explore_node});

            auto bat_at_explore = explore_node.tile->GetBattalion();
            if (explore_node.movement_left <= 0 ||
                (bat_at_explore != nullptr && bat_at_explore->GetTeam() != team))
            {
                continue;
            }

            GetTileNeighbours(&neighbours, explore_node.tile);
            for (auto neighbour : neighbours)
            {
                auto neighbour_pos = neighbour->GetDiscretePos();
                if (explored.count(PosToIndex(neighbour_pos)) == 0)
                {
                    auto moveCost = neighbour->GetMoveCost(team);
                    frontier.insertKey(ExploreNode{neighbour,
                                                   explore_node.cost + moveCost,
                                                   explore_node.movement_left - moveCost,
                                                   explore_pos_i});
                }
            }
        }

        auto start_i = x + y * width;
        for (auto v : explored)
        {
            auto action = action_t(v.second.tile, new std::vector<Tile *>());
            action.second->push_back(action.first);
            auto prev_i = v.second.prev_i;
            while (prev_i != start_i)
            {
                action.second->push_back(tiles->at(prev_i));
                prev_i = explored.at(prev_i).prev_i;
            }
            action.second->push_back(tiles->at(start_i));
            res->push_back(action);
        }

        return res;
    }

    float Map::CostToTile(std::vector<Tile *> *path)
    {
        return path != nullptr ? path->size() : -1.f;
    }
}