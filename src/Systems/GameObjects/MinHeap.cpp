#include "MinHeap.hpp"

namespace egl
{

    MinHeap::MinHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        harr = new ExploreNode[cap];
    }

    void MinHeap::insertKey(ExploreNode k)
    {
        if (heap_size == capacity)
        {
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)].cost > harr[i].cost)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    void MinHeap::decreaseKey(int i, ExploreNode new_val)
    {
        harr[i] = new_val;
        while (i != 0 && harr[parent(i)].cost > harr[i].cost)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    ExploreNode MinHeap::extractMin()
    {
        if (heap_size <= 0)
            return ExploreNode{nullptr, 0.f, -1};
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        auto root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    void MinHeap::MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l].cost < harr[i].cost)
            smallest = l;
        if (r < heap_size && harr[r].cost < harr[smallest].cost)
            smallest = r;
        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }

    void swap(ExploreNode *x, ExploreNode *y)
    {
        auto temp = *x;
        *x = *y;
        *y = temp;
    }
}
