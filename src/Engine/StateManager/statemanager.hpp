#pragma once

#include <vector>

#include "state.hpp"
#include "../Drawable/drawable.hpp"
#include "../../Systems/Npc/Npc.hpp"

namespace egl
{
    class UIManager;
    class StateManager
    {
    private:
        static StateManager *pinstance_;
        static std::mutex mutex_;
        State *state;
        Npc npc = Npc();

        Entity *selected = nullptr;
        Entity *hover = nullptr;
        int currentTurn = 0;
        int currentPlayer = 0;

        std::vector<interaction_t> *aiMoves = nullptr;
        std::chrono::_V2::system_clock::time_point lastMovePerformed = std::chrono::high_resolution_clock::now();

    protected:
        StateManager();
        ~StateManager() {}

        void PlanNpcTurn();
        void HandleNpcMove();

        void InternalNextTurn();

    public:
        StateManager(StateManager &other) = delete;
        void operator=(const StateManager &) = delete;
        static StateManager *GetInstance();

        std::vector<EgDrawable *> *GetDrawables();

        void ClickAt(float x, float y, sf::Mouse::Button button);
        void MouseAt(float x, float y);
        void NextTurn(sf::Mouse::Button button);

        Entity *GetSelected();

        static constexpr int turnLimit = 8;
    };
}