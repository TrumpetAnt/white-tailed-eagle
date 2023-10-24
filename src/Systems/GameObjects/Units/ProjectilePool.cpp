#include "ProjectilePool.hpp"
#include "../Factories/EntityFactory.hpp"

namespace egl
{
    ProjectilePool *ProjectilePool::pinstance_{nullptr};
    std::mutex ProjectilePool::mutex_;

    ProjectilePool *ProjectilePool::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new ProjectilePool();
        }
        return pinstance_;
    }

    ProjectilePool::ProjectilePool()
    {
        for (int i = 0; i < 10; i++)
        {
            auto p = EntityFactory::GetBattalionProjectile();
            pool->push_back(p);
        }
    }

    void ProjectilePool::TrackEntities(std::vector<Entity *> *vec)
    {
        for (auto projectile : *pool)
        {
            vec->push_back(projectile);
        }
    }

    void ProjectilePool::Shoot(sf::Vector2f from, sf::Vector2f dest, int steps)
    {
        for (auto projectile : *pool)
        {
            if (projectile->MarkedForDestruction())
            {
                projectile->Shoot(from, dest, steps);
                return;
            }
        }

        throw std::length_error("Too many active projectiles");
    }
}
