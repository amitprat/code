#include "../header.h"

class KthLargestElement {
   public:
    static void test() {
        KthLargestElement obj;
        vector<int> arr = {11, 3, 2, 1, 15, 5, 4, 45, 88, 96, 50, 45};
        for (int i = 0; i <= 20; i++) {
            auto res = obj.kthLargestUsingHeap(arr, i);
            cout << format("{}th largest element : {}", i, res) << endl;
        }

        cout << "Print k largest elements:" << endl;
        for (int i = 0; i <= 20; i++) {
            obj.printKLargestElements(arr, i);
        }
    }

   private:
    int kthLargestUsingSorting(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end(), [](const auto& f, const auto& s) { return f > s; });

        return arr[k - 1];
    }

   private:
    int kthLargest(vector<int>& arr, int k) {
        return kthLargest(arr, 0, arr.size() - 1, k);
    }
    int kthLargest(vector<int>& arr, int l, int r, int k) {
        if (l > r) return INT_MIN;

        int p = partition(arr, l, r);
        int q = r - p + 1;  // larger elements on right

        if (k == q)
            return arr[p];
        else if (q < k)
            return kthLargest(arr, l, p - 1, k - q);
        else
            return kthLargest(arr, p + 1, r, k);
    }
    int partition(vector<int>& arr, int l, int r) {
        int pivot = arr[r];
        int low = l;
        for (int i = l; i < r; i++) {
            if (arr[i] <= pivot) {
                swap(arr[low++], arr[i]);
            }
        }
        swap(arr[low], arr[r]);

        return low;
    }

   private:
    void printKLargestElements(vector<int>& arr, int k) {
        auto pos = kthLargestIndex(arr, 0, arr.size() - 1, k);
        for (int i = pos; i < arr.size(); i++) cout << arr[i] << " ";
        cout << endl;
    }
    int kthLargestIndex(vector<int>& arr, int l, int r, int k) {
        if (l > r) return INT_MIN;

        int p = partition(arr, l, r);
        int q = r - p + 1;  // larger elements on right

        if (k == q)
            return p;
        else if (q < k)
            return kthLargestIndex(arr, l, p - 1, k - q);
        else
            return kthLargestIndex(arr, p + 1, r, k);
    }

   private:
    template <class T>
    class Heap {
        vector<T> arr;
        int sz = 0;
        std::function<bool(const T&, const T&)> compare;

       public:
        Heap(std::function<bool(const T&, const T&)> compare) : compare(compare) {}

        void push(T e) {
            arr.push_back(e);
            sz++;

            upHeapify(sz - 1);
        }

        T top() {
            return arr[0];
        }

        T pop() {
            auto e = arr[0];
            arr[0] = arr[sz - 1];
            sz--;

            downHeapify(0);

            return e;
        }

        bool empty() {
            return sz == 0;
        }

       private:
        void upHeapify(int idx) {
            T p = parent(idx);
            while (idx != 0 && compare(arr[p], arr[idx])) {
                swap(arr[idx], arr[p]);
                idx = p;
                p = parent(idx);
            }
        }

        void downHeapify(int idx) {
            int largestIndex = idx;

            int l = left(idx);
            if (l < sz && compare(arr[largestIndex], arr[l])) largestIndex = l;

            int r = right(idx);
            if (r < sz && compare(arr[largestIndex], arr[r])) largestIndex = r;

            if (idx != largestIndex) {
                swap(arr[idx], arr[largestIndex]);

                downHeapify(largestIndex);
            }
        }

        int parent(int idx) { return (idx - 1) / 2; }
        int left(int idx) { return 2 * idx + 1; }
        int right(int idx) { return 2 * idx + 2; }
    };
    int kthLargestUsingHeap(vector<int>& arr, int k) {
        Heap<int> heap([](const auto& f, const auot& s) { return f < s; });
        for (auto& e : arr) heap.push(e);

        int elem = INT_MIN;
        while (!heap.empty() && k--) {
            elem = heap.pop();
        }

        return k > 0 ? INT_MIN : elem;
    }
};