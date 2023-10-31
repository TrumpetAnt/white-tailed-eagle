#pragma once

#include <mutex>
#include <vector>
#include <stdexcept>
#include "PathSegment.hpp"
#include "../Tile.hpp"

namespace egl
{
    class EntityFactory;
    class PathSegmentPool
    {
    private:
        static PathSegmentPool *pinstance_;
        static std::mutex mutex_;
        std::vector<PathSegment *> *pool = new std::vector<PathSegment *>();
        int activeCount = 0;

    protected:
        PathSegmentPool();
        ~PathSegmentPool() {}

        void addSegments(int n);

    public:
        PathSegmentPool(PathSegmentPool &other) = delete;
        void operator=(const PathSegmentPool &) = delete;
        static PathSegmentPool *GetInstance();

        void TrackEntities(std::vector<Entity *> *vec);

        // @todo: Add small dots and points between path segments
        void MarkMovePath(std::vector<Tile *> *tiles, bool attackLast = false);
        void UnMarkPath();
    };
}
