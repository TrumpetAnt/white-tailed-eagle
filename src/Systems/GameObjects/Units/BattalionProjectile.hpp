#pragma once

#include "../../../Engine/Entity/entity.hpp"
#include "../EntityType.hpp"
#include "../TransformUtils.hpp"

namespace egl
{
    class BattalionProjectile : public Entity
    {
    private:
        sf::Vector2f stepDelta = sf::Vector2f(0.f, 0.f);
        sf::Vector2f dest = sf::Vector2f(0.f, 0.f);
        int steps_left = 0;

        void Step();

    public:
        BattalionProjectile();

        bool MarkedForDestruction() override;
        bool IsDrawable() override;
        void ConcatDrawable(std::vector<EgDrawable *> *res) override;

        void Shoot(sf::Vector2f from, sf::Vector2f dest, int steps);
    };
}
