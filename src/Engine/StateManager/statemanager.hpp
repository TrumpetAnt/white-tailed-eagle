#pragma once

#include <vector>

#include "state.hpp"
#include "../Drawable/drawable.hpp"

namespace egl
{
    class StateManager
    {
    private:
        State *state;

    public:
        StateManager();

        std::vector<EgDrawable *> *GetDrawables();
    };
}