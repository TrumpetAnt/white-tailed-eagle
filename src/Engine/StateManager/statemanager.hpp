#pragma once

#include <vector>

#include "state.hpp"
#include "../Drawable/drawable.hpp"

namespace egl
{
    class StateManager
    {
    private:
        static StateManager *pinstance_;
        static std::mutex mutex_;
        State *state;
        Entity *selected = nullptr;

    protected:
        StateManager();
        ~StateManager() {}

    public:
        StateManager(StateManager &other) = delete;
        void operator=(const StateManager &) = delete;
        static StateManager *GetInstance();

        std::vector<EgDrawable *> *GetDrawables();

        void ClickAt(float x, float y, sf::Mouse::Button button);
        void NextTurn(sf::Mouse::Button button);
    };
}