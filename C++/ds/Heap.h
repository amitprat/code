#include "header.h"

template <class T>
class PriorityQueue
{
private:
    vector<T> keys;
    function<bool(T, T)> comp;

public:
    PriorityQueue(function<bool(T, T)> comp) : comp(comp) {}

    void insert(vector<T> keys)
    {
        for (auto &key : keys)
        {
            this->keys.push_back(key);
        }

        this->buildHeap();
    }

    void insert(T key)
    {
        this->keys.push_back(key);

        this->upHeapify(this->size() - 1);
    }

    void remove(T key)
    {
        int pos = find(key);
        swap(keys[pos], keys[this->size() - 1]);
        keys.pop_back();

        this->down_heapify(pos);
    }

    T top()
    {
        if (empty())
            throw exception("Empty");

        return keys[0];
    }

    T pop()
    {
        if (empty())
            throw exception("Empty");

        T val = keys[0];
        keys[0] = keys[this->size() - 1];
        keys.pop_back();

        this->down_heapify(0);

        return val;
    }

    bool empty()
    {
        return keys.size() <= 0;
    }

private:
    void buildHeap()
    {
        int n = this->size();
        int s = (n - 1) / 2;

        for (int i = s; i >= 0; i--)
        {
            this->down_heapify(i);
        }
    }

    void down_heapify(int i)
    {
        int n = this->size();
        int l = this->left(i);
        int r = this->right(i);

        int idx = i;
        if (l < n && this->comp(keys[l], keys[idx]))
            idx = l;
        if (r < n && this->comp(keys[r], keys[idx]))
            idx = r;

        if (idx != i)
        {
            swap(keys[i], keys[idx]);
            down_heapify(idx);
        }
    }

    void upHeapify(int i)
    {
        int p = this->parent(i);

        while (i != 0 && !this->comp(keys[p], keys[i]))
        {
            swap(keys[p], keys[i]);
            i = p;
            p = this->parent(i);
        }
    }

    int find(T key)
    {
        for (int i = 0; i < keys.size(); i++)
        {
            if (keys[i] == key)
                return i;
        }

        throw exception("Not found");
    }

    inline int left(int i) { return 2 * i + 1; }
    inline int right(int i) { return 2 * i + 2; }
    inline int parent(int i) { return (i - 1) / 2; }
    inline int size() { return keys.size(); }
};

class PriorityQueueTester
{
public:
    static void test()
    {
        PriorityQueue<int> pq([](int x, int y)
                              { return x < y; });

        pq.insert({3, 1, 2});
        pq.insert(10);
        pq.insert(0);
        pq.insert(4);

        while (!pq.empty())
        {
            cout << pq.pop() << " ";
        }

        cout << endl;
        pq.insert(10);
        pq.insert(0);
        pq.insert(4);
        pq.insert({3, 1, 2});
        while (!pq.empty())
        {
            cout << pq.pop() << " ";
        }

        cout << endl;
    }
};