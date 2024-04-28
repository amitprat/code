#pragma once
#include "../header.h"

template <class T>
class Minheap {
   private:
    vector<T> arr;
    int n = 10;
    int size = 0;

    function<bool(const T& first, const T& second)> comparator;

   public:
    Minheap(const vector<T>& arr) : arr(arr) {}
    ~Minheap() { delete arr; }

    void push(T key) {
        if (isFull()) resize();

        size++;
        heap[size] = INT_MAX;
        decreaseKey(size - 1, key);
    }

    T top() {
        if (empty()) throw runtime_error("Empty");

        return arr[0];
    }

    T pop() {
        if (empty()) throw runtime_error("Empty");

        auto top = arr[0];
        arr[0] = arr[size - 1];
        size--;

        downHeapify(0);

        return top;
    }

   public:
    int getSize() { return size; }

    bool isFull() {
        return arr.size() == n;
    }
    bool empty() {
        return arr.empty();
    }

   private:
    void resize() {
        T* newheap = new T[n * 2];
        for (int i = 0; i < size; i++) {
            new_heap[i] = heap[i];
        }
        n *= 2;
        delete[] heap;
        heap = newheap;
    }

   private:
    void buildHeap() {
        for (int i = (size - 1) / 2; i >= 0; i--) {
            downHeapify(i);
        }
    }

    void downHeapify(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && compare(arr[l], arr[i]) < 0) {
            smallest = l;
        }
        if (r < size && compare(arr[r], arr[i]) < 0) {
            smallest = r;
        }

        if (smallest != i) {
            swap(&arr[i], &arr[smallest]);
            downHeapify(smallest);
        }
    }

    void upHeapify(int i) {
        int p = parent(i);
        while (i != 0 && compare(arr[i], arr[parent]) < 0) {
            swap(arr[i], arr[p]);
            i = p;
            p = parent(i);
        }
    }

    void decreaseKey(int i, int key) {
        arr[i] = key;
        int p = parent(i);

        while (p != 0 && compare(arr[i], arr[p]) < 0) {
            swap(arr[i], arr[p]);
            p = i;
            p = parent(i);
        }
    }

   private:
    int left(int i) {
        return (2 * i + 1);
    }
    int right(int i) {
        return (2 * i + 2);
    }
    int parent(int i) {
        return (i - 1) / 2;
    }
};
