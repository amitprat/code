#pragma once
#include "../Header.h"
using namespace std;

const int SIZE = 10000;

class FindTopKElements {
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
        int parent(int pos) { return (pos - 1) / 2; }
        int left(int pos) { return 2 * pos + 1; }
        int right(int pos) { return 2 * pos + 2; }

        void heapify(int pos)
        {
            int min = pos;
            if (left(pos) < size && arr[left(pos)] < arr[pos]) min = left(pos);
            if (right(pos) < size && arr[right(pos)] < arr[pos]) min = right(pos);

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

public:
    static void test()
    {
        std::mutex m;
        condition_variable cv;

        int k = 5;
        std::atomic<bool> newItemAvailable(false);
        atomic<int> iterations = 100;
        srand(time(NULL));
        BitSet bitset;

        auto pub = thread([&bitset, &m, &cv, &newItemAvailable, &iterations]() {
            while (1) {
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, [&]() { return newItemAvailable == false; });

                int elem = rand() % SIZE;
                cout << "Adding : " << elem << endl;
                bitset.add(elem);

                newItemAvailable = true;
                iterations--;
                cv.notify_all();
                if (iterations <= 0) break;
            }
            });

        auto sub = thread([&bitset, k, &cv, &m, &newItemAvailable, &iterations]() {
            while (1) {
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, [&]() { return newItemAvailable == true; });

                auto result = bitset.top(k);
                cout << format("Top k elements: {}", to_string(result)) << endl;

                newItemAvailable = false;
                iterations--;
                cv.notify_all();
                if (iterations <= 0) break;
            }
            });

        pub.join();
        sub.join();

        vector<int> nums;
        for (int i = 0; i < 100; i++) nums.push_back(rand() % SIZE);
        cout << to_string(nums) << endl;

        // it will only consider unique elements
        cout << "Using BitSet Method:";
        BitSet set;
        for (auto num : nums) set.add(num);

        auto result = set.top(k);
        cout << to_string(result) << endl;

        // It will include duplicate elements
        cout << "Using Heap Method:";
        MinHeap heap(k);
        for (auto num : nums) heap.add(num);

        while (!heap.empty()) cout << heap.pop() << " ";
        cout << endl;

        cout << "Top K elements using sorting: ";
        sort(nums.begin(), nums.end());
        while (k--) {
            cout << nums.back() << ", ";
            nums.pop_back();
        }
        cout << endl;
    }
};