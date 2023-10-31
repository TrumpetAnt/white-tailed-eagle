#include "statemanager.hpp"

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

    std::vector<EgDrawable *> *StateManager::GetDrawables()
    {
        auto res = new std::vector<EgDrawable *>();
        auto entities = state->GetEntities();
        for (auto entity : *entities)
        {
            if (entity->IsDrawable())
            {
                entity->ConcatDrawable(res);
            }
        }

        return res;
    }

    void StateManager::ClickAt(float x, float y, sf::Mouse::Button button)
    {
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

    void StateManager::NextTurn(sf::Mouse::Button button)
    {
        if (button != sf::Mouse::Button::Left)
        {
            return;
        }
        state->NextTurn();
    }

    Entity *StateManager::GetSelected()
    {
        return selected;
    }
}