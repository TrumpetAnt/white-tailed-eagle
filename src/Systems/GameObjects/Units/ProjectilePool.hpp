#pragma once

#include <mutex>
#include <vector>
#include <stdexcept>
#include "BattalionProjectile.hpp"

namespace egl
{
    class EntityFactory;
    class ProjectilePool
    {
    private:
        static ProjectilePool *pinstance_;
        static std::mutex mutex_;
        std::vector<BattalionProjectile *> *pool = new std::vector<BattalionProjectile *>();

    protected:
        ProjectilePool();
        ~ProjectilePool() {}

    public:
        ProjectilePool(ProjectilePool &other) = delete;
        void operator=(const ProjectilePool &) = delete;
        static ProjectilePool *GetInstance();

        void TrackEntities(std::vector<Entity *> *vec);

        void Shoot(sf::Vector2f from, sf::Vector2f dest, int steps);
    };
}
