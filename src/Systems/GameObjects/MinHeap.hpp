#pragma once

#include <limits>

namespace egl
{
    class Tile;

    struct ExploreNode
    {
        Tile *tile;
        float cost;
        float movement_left;
        int prev_i;
    };

    void swap(ExploreNode *x, ExploreNode *y);

    class MinHeap
    {
        ExploreNode *harr; // pointer to array of elements in heap
        int capacity;      // maximum possible size of min heap
        int heap_size;     // Current number of elements in min heap
    private:
        int parent(int i) { return (i - 1) / 2; }
        int left(int i) { return (2 * i + 1); }
        int right(int i) { return (2 * i + 2); }
        void decreaseKey(int i, ExploreNode new_val);

    public:
        MinHeap(int capacity);

        void MinHeapify(int);

        ExploreNode extractMin();

        ExploreNode getMin() { return harr[0]; }

        void insertKey(ExploreNode k);

        bool isEmpty() { return heap_size == 0; }
    };

}
