#include "PathSegmentPool.hpp"
#include "../Factories/EntityFactory.hpp"

namespace egl
{
    PathSegmentPool *PathSegmentPool::pinstance_{nullptr};
    std::mutex PathSegmentPool::mutex_;

    PathSegmentPool *PathSegmentPool::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstance_ == nullptr)
        {
            pinstance_ = new PathSegmentPool();
        }
        return pinstance_;
    }

    PathSegmentPool::PathSegmentPool()
    {
        addSegments(20);
    }

    void PathSegmentPool::addSegments(int n)
    {
        for (int i = 0; i < n; i++)
        {
            auto p = EntityFactory::GetPathSegment();
            pool->push_back(p);
        }
    }

    void PathSegmentPool::TrackEntities(std::vector<Entity *> *vec)
    {
        for (auto pathSegment : *pool)
        {
            vec->push_back(pathSegment);
        }
    }

    void PathSegmentPool::MarkMovePath(std::vector<Tile *> *tiles, bool attackLast)
    {
        if (tiles->size() < 2)
        {
            return;
        }
        if (tiles->size() > pool->size())
        {
            auto sizeDiff = tiles->size() - pool->size();
            addSegments(sizeDiff);
        }
        auto prev = tiles->at(0);
        auto end = tiles->size();
        for (auto i = 1; i < end; i++)
        {
            auto segment = pool->at(i - 1);
            auto current = tiles->at(i);
            segment->Show(prev->getPosition(), current->getPosition(), attackLast && i == 1);
            prev = current;
        }
        activeCount = tiles->size();
    }

    void PathSegmentPool::UnMarkPath()
    {
        auto it = pool->begin();
        for (int i = 0; i < activeCount; i++)
        {
            (*it)->Hide();
            it++;
        }
        activeCount = 0;
    }
}
