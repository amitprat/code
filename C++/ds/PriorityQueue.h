#include "../header.h"
using namespace std;

template <typename T>
concept Comparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
};

template <Comparable T>
class PriorityQueue {
   private:
    vector<T> heap;
    function<bool(const T&, const T&)> comparator;

   public:
    using iterator = typename vector<T>::iterator;
    using const_iterator = typename vector<T>::const_iterator;

    explicit PriorityQueue(function<bool(const T&, const T&)> comp) : comparator(std::move(comp)) {}

    void insert(const vector<T>& values) {
        for (const auto& val : values) {
            heap.push_back(val);
        }
        buildHeap();
    }

    void insert(const T& value) {
        heap.push_back(value);
        upHeapify(heap.size() - 1);
    }

    void remove(const T& value) {
        int index = find(value);
        swap(heap[index], heap.back());
        heap.pop_back();
        if (index < heap.size()) {
            downHeapify(index);
            upHeapify(index);
        }
    }

    const T& top() const {
        if (empty()) throw runtime_error("PriorityQueue is empty.");
        return heap.front();
    }

    T pop() {
        if (empty()) throw runtime_error("PriorityQueue is empty.");
        T topElement = heap.front();
        heap.front() = heap.back();
        heap.pop_back();
        downHeapify(0);
        return topElement;
    }

    bool empty() const noexcept {
        return heap.empty();
    }

    size_t size() const noexcept {
        return heap.size();
    }

    iterator begin() noexcept { return heap.begin(); }
    iterator end() noexcept { return heap.end(); }
    const_iterator begin() const noexcept { return heap.begin(); }
    const_iterator end() const noexcept { return heap.end(); }
    const_iterator cbegin() const noexcept { return heap.cbegin(); }
    const_iterator cend() const noexcept { return heap.cend(); }

   private:
    void buildHeap() {
        int n = heap.size();
        int s = (n - 1) / 2;
        for (int i = s; i >= 0; --i) {
            downHeapify(i);
        }
    }

    void down_heapify_rec(int i) {
        int n = this->size();
        int l = this->left(i);
        int r = this->right(i);

        int idx = i;
        if (l < n && this->comp(keys[l], keys[idx])) idx = l;
        if (r < n && this->comp(keys[r], keys[idx])) idx = r;

        if (idx != i) {
            swap(keys[i], keys[idx]);
            down_heapify(idx);
        }
    }

    void down_heapify(size_t i) {
        size_t n = heap.size();

        while (true) {
            size_t smallest = i;
            size_t leftChild = left(i);
            size_t rightChild = right(i);

            if (leftChild < n && comparator(heap[leftChild], heap[smallest])) smallest = leftChild;
            if (rightChild < n && comparator(heap[rightChild], heap[smallest])) smallest = rightChild;

            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            } else {
                break;
            }
        }
    }

    void upHeapify(size_t i) {
        while (i > 0 && comparator(heap[i], heap[parent(i)])) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    int find(const T& value) const {
        auto it = std::find(heap.begin(), heap.end(), value);
        if (it == heap.end()) throw runtime_error("Element not found in PriorityQueue.");
        return distance(heap.begin(), it);
    }

    constexpr size_t left(size_t i) const noexcept { return 2 * i + 1; }
    constexpr size_t right(size_t i) const noexcept { return 2 * i + 2; }
    constexpr size_t parent(size_t i) const noexcept { return (i - 1) / 2; }

   public:
    static void test() {
        PriorityQueue<int> pq([](int x, int y) { return x < y; });

        pq.insert({3, 1, 2});
        pq.insert(10);
        pq.insert(0);
        pq.insert(4);

        cout << "PriorityQueue output 1: ";
        for (int val : pq) cout << val << " ";
        cout << endl;

        while (!pq.empty()) cout << pq.pop() << " ";
        cout << endl;

        pq.insert({10, 0, 4});
        pq.insert({3, 1, 2});

        cout << "PriorityQueue output 2: ";
        for (int val : pq) cout << val << " ";
        cout << endl;

        while (!pq.empty()) cout << pq.pop() << " ";
        cout << endl;

        cout << "All tests passed.\n";
    }
};