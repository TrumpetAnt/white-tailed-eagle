#include "statemanager.hpp"

#include "../UIManager/uimanager.hpp"

namespace egl
{
    StateManager *StateManager::pinstance_{nullptr};
    std::mutex StateManager::mutex_;

    StateManager *StateManager::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new StateManager();
        }
        return pinstance_;
    }

    StateManager::StateManager()
    {
        state = new State();
    }

    void StateManager::PlanNpcTurn()
    {
        currentPlayer += 1;
        aiMoves = npc.GetInteractions(state);
        std::cout << aiMoves->size() << " AI moves planned" << std::endl;
        lastMovePerformed = std::chrono::high_resolution_clock::now();
    }

    void StateManager::HandleNpcMove()
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        if (t0 - lastMovePerformed < std::chrono::milliseconds(100))
        {
            return;
        }
        lastMovePerformed = t0;
        if (aiMoves == nullptr || aiMoves->size() == 0)
        {
            InternalNextTurn();
            if (aiMoves != nullptr)
            {
                delete aiMoves;
            }
            aiMoves = nullptr;
            return;
        }
        auto move = aiMoves->at(aiMoves->size() - 1);
        aiMoves->pop_back();
        move.second->InteractWithEntity(move.first);
        std::cout << "NpcMove performed" << std::endl;
    }

    std::vector<EgDrawable *> *StateManager::GetDrawables()
    {
        if (currentPlayer != 0)
        {
            HandleNpcMove();
        }

        auto entities = state->GetEntities();
        for (auto entity : *entities)
        {
            if (entity->IsDrawable())
            {
                entity->ConcatDrawable(drawablesMap);
            }
        }
        auto keys = std::vector<int>();

        for (auto elem : *drawablesMap)
        {
            keys.push_back(elem.first);
        }

        std::sort(keys.begin(), keys.end());

        auto res = new std::vector<EgDrawable *>();

        for (auto key : keys)
        {
            for (auto elem : *drawablesMap->at(key))
            {
                res->push_back(elem);
            }

            drawablesMap->at(key)->clear();
        }
        drawablesMap->clear();
        return res;
    }

    void StateManager::ClickAt(float x, float y, sf::Mouse::Button button)
    {
        if (currentPlayer != 0)
        {
            return;
        }
        if (selected == nullptr && button == sf::Mouse::Button::Left)
        {
            auto target = state->SelectAt(x, y);
            if (target != nullptr && target->IsSelectable())
            {
                selected = target;
                std::cout << "Selected entity" << std::endl;
                selected->Highlight();
            }
        }
        else if (selected != nullptr)
        {
            if (button == sf::Mouse::Button::Right)
            {
                auto target = state->SelectAt(x, y);
                if (target != nullptr && target->InteractWithEntity(selected))
                {
                    std::cout << "Deselect entity" << std::endl;
                    selected->ResetHighlight();
                    selected = nullptr;
                }
            }
            if (button == sf::Mouse::Button::Left)
            {
                auto target = state->SelectAt(x, y);
                if (target != nullptr &&
                    target->GetEntityType() == selected->GetEntityType() &&
                    selected != target &&
                    target->IsSelectable())
                {
                    std::cout << "Select another entity of same type" << std::endl;
                    selected->ResetHighlight();
                    selected = target;
                    selected->Highlight();
                    return;
                }
                std::cout << "Deselect entity" << std::endl;
                selected->ResetHighlight();
                selected = nullptr;
            }
        }
    }

    void StateManager::MouseAt(float x, float y)
    {
        auto target = state->SelectAt(x, y);
        if (hover == target)
        {
            return;
        }
        if (hover != nullptr)
        {
            hover->StopHover();
        }
        hover = target;
        if (hover == nullptr)
        {
            return;
        }
        hover->Hover();
    }

    void StateManager::InternalNextTurn()
    {
        currentPlayer = 0;
        state->NextTurn();
        auto uiManager = UIManager::GetInstance(nullptr);
        uiManager->IndicateNextTurn();
        currentTurn += 1;
        if (currentTurn == turnLimit)
        {
            uiManager->EndOfGame();
        }
    }

    void StateManager::NextTurn(sf::Mouse::Button button)
    {
        if (button != sf::Mouse::Button::Left)
        {
            return;
        }
        PlanNpcTurn();
    }

    void StateManager::Mystery()
    {
        state->Mystery();
    }

    Entity *StateManager::GetSelected()
    {
        return selected;
    }
}