#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;
const int SIZE = 10000;

class BitSet
{
public:
    BitSet()
    {
        for (int i = 0; i < SIZE; i++) nums[i] = 0;
    }
    void add(int num)
    {
        set(num);
    }

    vector<int> top(int n)
    {
        int  cnt = 0;
        vector<int> result;
        for (int i = SIZE - 1; i >= 0; i--)
        {
            for (int j = 31; j >= 0; j--)
            {
                if (get(i, j) && cnt++ < n) {
                    // cout << "Getting at" << i << "," << j << endl;
                    result.push_back(i * 32 + j);
                }
            }
        }

        return result;
    }

private:
    void set(int pos)
    {
        // cout << "Setting :" << pos << " at" << (pos / 32) << "," << (pos % 32) << endl;
        nums[pos / 32] |= 1 << (pos % 32);
    }

    bool get(int pos1, int pos2)
    {
        return nums[pos1] & (1 << (pos2));
    }

    int nums[SIZE];
};

class MinHeap
{
public:
    MinHeap(int capacity)
    {
        this->capacity = capacity;
        arr = new int[capacity];
    }
    ~MinHeap() {
        delete[] arr;
    }

    bool empty() { return size == 0; }
    int length() { return size; }
    int top() { return arr[0]; }
    int pop() {
        int top = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapify(0);
        return top;
    }

    void add(int item)
    {
        if (size < capacity) {
            size++;
            decreaseKey(size - 1, item);
        }
        else if (item > top())
        {
            arr[0] = item;
            heapify(0);
        }
    }

private:
    int parent(int pos) { return pos / 2; }
    int left(int pos) { return 2 * pos + 1; }
    int right(int pos) { return 2 * pos + 2; }
    void heapify(int pos)
    {
        int min = pos;
        if (left(pos) < size && arr[left(pos)] <= arr[pos]) min = left(pos);
        if (right(pos) < size && arr[right(pos)] <= arr[pos]) min = right(pos);
        if (min != pos)
        {
            swap(arr[min], arr[pos]);
            heapify(min);
        }
    }

    void decreaseKey(int i, int new_val)
    {
        arr[i] = new_val;
        while (i != 0 && arr[parent(i)] > arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    int size = 0;
    int capacity = 0;
    int* arr = nullptr;
};

void dump(vector<int> arr, bool debug)
{
    if (debug) {
        cout << "Dump Arr:";
        for (auto i : arr) cout << i << " ";
        cout << endl;
    }
}

void tester()
{
    std::mutex m;
    int arrSize = 10000;
    int maxElemSize = 5;
    int numLimit = 10000;
    std::atomic<bool> newItemAvailable(false);
    srand(time(NULL));
    vector<int> nums;

    auto pub = thread([&nums, numLimit, &m, &newItemAvailable]() {
        while (1) {
            std::lock_guard<std::mutex> lock(m);
            int elem = rand() % numLimit;
            cout << "Adding : " << elem << endl;
            nums.push_back(elem);
            newItemAvailable = true;
        }
        });
    auto sub = thread([&nums, maxElemSize, &m, &newItemAvailable]() {
        while (1) {
            std::lock_guard<std::mutex> lock(m);
            if (newItemAvailable) {
                BitSet set;
                for (auto num : nums) set.add(num);
                auto result = set.top(maxElemSize);
                cout << "Extracting top elements : ";
                for (auto r : result) cout << r << " ";
                cout << endl;
                newItemAvailable = false;
            }
        }
        });

    cout << "Waiting for 10 second...";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pub.join();
    sub.join();

    //for (int i = 0; i < arrSize; i++) nums.push_back(rand() % numLimit);
    //dump(nums, false);

    //cout << "Using BitSet Method:";
    //BitSet set;
    //for (auto num : nums) set.add(num);
    //auto result = set.top(maxElemSize);
    //for (int i = 0; i < maxElemSize; i++) cout << result[i] << " ";
    //cout << endl;

    //cout << "Using Heap Method:";
    //MinHeap heap(maxElemSize);
    //for (int i = 0; i < arrSize; i++) heap.add(nums[i]);

    //while (!heap.empty()) cout << heap.pop() << " ";
    //cout << endl;
}