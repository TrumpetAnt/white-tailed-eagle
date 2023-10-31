#pragma once

#include <vector>

#include "state.hpp"
#include "../Drawable/drawable.hpp"

namespace egl
{
    class UIManager;
    class StateManager
    {
    private:
        static StateManager *pinstance_;
        static std::mutex mutex_;
        State *state;
        Entity *selected = nullptr;
        Entity *hover = nullptr;
        int currentTurn = 0;

    protected:
        StateManager();
        ~StateManager() {}

    public:
        StateManager(StateManager &other) = delete;
        void operator=(const StateManager &) = delete;
        static StateManager *GetInstance();

        std::vector<EgDrawable *> *GetDrawables();

        void ClickAt(float x, float y, sf::Mouse::Button button);
        void MouseAt(float x, float y);
        void NextTurn(sf::Mouse::Button button);

        Entity *GetSelected();

        static constexpr int turnLimit = 10;
    };
}