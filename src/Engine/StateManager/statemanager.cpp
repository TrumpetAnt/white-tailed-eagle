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
            selected = state->SelectAt(x, y);
            if (selected != nullptr)
            {
                std::cout << "Selected entity" << std::endl;
                selected->Highlight();
            }
        }
        else if (selected != nullptr && (button == sf::Mouse::Button::Left || button == sf::Mouse::Button::Right))
        {
            std::cout << "Deselect entity" << std::endl;
            selected->ResetHighlight();
            selected = nullptr;
        }
    }
}