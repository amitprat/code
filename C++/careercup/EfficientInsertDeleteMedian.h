#include "../header.h"

class EfficientInsertDeleteMedian {
    class EfficientInsertDeleteMedianUsingHeap {
        priority_queue<int> maxHeap;                             // left
        priority_queue<int, vector<int>, greater<int>> minHeap;  // right
        unordered_map<int, int> delayed;
        int size = 0;

       public:
        void insert(int val) {
            minHeap.push(val);
            maxHeap.push(minHeap.top());
            minHeap.pop();
            prune(minHeap);

            if (minHeap.size() < maxHeap.size()) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                prune(maxHeap);
            }

            size++;
        }

        bool remove(int val) {
            delayed[val]++;
            size--;

            if (!maxHeap.empty() && val < maxHeap.top()) {
                prune(maxHeap);
            } else if (!minHeap.empty()) {
                prune(minHeap);
            }

            return true;
        }

        void prune(priority_queue<int>& heap) {
            while (!heap.empty() && delayed[heap.top()]) {
                delayed[heap.top()]--;
                heap.pop();
            }
        }

        void prune(priority_queue<int, vector<int>, greater<int>>& heap) {
            while (!heap.empty() && delayed[heap.top()]) {
                delayed[heap.top()]--;
                heap.pop();
            }
        }

        // O(1)
        double median() {
            if (size == 0) throw runtime_error("No elements.");
            if (size & 1) {
                return maxHeap.top();
            } else {
                return (minHeap.top() + maxHeap.top()) / 2;
            }
        }
    };

    class EfficientInsertDeleteMedianUsingMultiSet {
       private:
        multiset<int> ms;
        multiset<int>::iterator mid;

       public:
        void insert(int val) {
            if (ms.empty()) {
                ms.insert(val);
                mid = ms.begin();
            } else {
                ms.insert(val);
                if (val < *mid) {
                    if (!(ms.size() & 1)) mid--;
                } else {
                    if (ms.size() & 1) mid++;
                }
            }
        }

        bool remove(int val) {
            if (ms.find(val) == ms.end()) return false;

            if (val < *mid) {
                if (ms.size() & 1) mid++;
            } else {
                if (!(ms.size() & 1)) mid--;
            }

            ms.erase(val);

            return true;
        }

        double median() {
            if (ms.empty()) throw runtime_error("Empty set");

            int n = ms.size();
            if (n & 1) {
                return *mid;
            } else {
                return (*mid + *next(mid)) / 2;
            }
        }
    };

   public:
    static void test() {
        EfficientInsertDeleteMedianUsingHeap mh;
        mh.insert(10);
        mh.insert(20);
        mh.insert(30);
        cout << "Median: " << mh.median() << endl;  // 20

        mh.remove(20);
        cout << "Median after deleting 20: " << mh.median() << endl;  // 20 or 10

        mh.insert(40);
        cout << "Median: " << mh.median() << endl;  // 30
    }
};