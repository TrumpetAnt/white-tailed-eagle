#pragma once

#include <vector>

namespace egl
{
    class Tile;
    typedef std::pair<Tile *, std::vector<Tile *> *> action_t;
}
