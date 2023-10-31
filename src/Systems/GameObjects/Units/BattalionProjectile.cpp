#include "BattalionProjectile.hpp"

namespace egl
{
    BattalionProjectile::BattalionProjectile() : Entity(EntityType::E_BattalionProjectile) {}

    void BattalionProjectile::Step()
    {
        steps_left -= 1;
        SetPosition(getPosition() + stepDelta);
    }

    bool BattalionProjectile::IsDrawable()
    {
        return !MarkedForDestruction();
    }

    void BattalionProjectile::ConcatDrawable(std::vector<EgDrawable *> *res)
    {
        Step();
        res->push_back(drawable);
    }

    bool BattalionProjectile::MarkedForDestruction()
    {
        return steps_left <= 0;
    }

    void BattalionProjectile::Shoot(sf::Vector2f from, sf::Vector2f dest, int steps)
    {
        this->dest = dest;
        steps_left = steps;

        auto diff = dest - from;
        if (steps == 0)
        {
            return;
        }
        auto f_steps = static_cast<float>(steps);
        stepDelta = sf::Vector2f(diff.x / f_steps, diff.y / f_steps);

        auto angle = vecop::AngleBetweenVectors(sf::Vector2f(0.f, 1.f), diff);

        drawable->setRotation(diff.x > 0.f ? 360.f - angle : angle);
        setPosition(from);
    }
}
