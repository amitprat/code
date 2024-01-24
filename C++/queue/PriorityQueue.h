#pragma once
#include "../header.h"
using namespace std;

template<class T>
class PriorityQueue {
private:
    using Comparator = std::function<bool(const T&, const T&)>;
    vector<T> container;
    Comparator comparator;

public:
    PriorityQueue() {
        comparator = [](const T& a, const T& b) { return a < b; };
    }
    PriorityQueue(Comparator comparator) :comparator(std::move(comparator)) {}

    void add(T item) {
        container.push_back(item);
        upHeapify(container.size() - 1);
    }

    T top() {
        if (container.empty()) return T();
        return container[0];
    }

    T pop() {
        auto res = top();
        swap(container[0], container[container.size() - 1]);
        container.pop_back();
        downHeapify();
        return res;
    }

    bool empty() { return container.empty(); }

private:
    void downHeapify(int startIndex = 0) {
        int mnIndex = startIndex;
        int leftIndex = left(startIndex);
        if (leftIndex < container.size() && comparator(container[leftIndex], container[mnIndex])) mnIndex = leftIndex;
        int rightIndex = right(startIndex);
        if (rightIndex < container.size() && comparator(container[rightIndex], container[mnIndex])) mnIndex = rightIndex;
        if (mnIndex != startIndex) {
            swap(container[mnIndex], container[startIndex]);
            downHeapify(mnIndex);
        }
    }

    void upHeapify(int startIndex) {
        int p = parent(startIndex);
        while (startIndex != 0 && !comparator(container[p], container[startIndex])) {
            swap(container[p], container[startIndex]);
            startIndex = p;
            p = parent(startIndex);
        }
    }

    int parent(int index) { return index / 2; }
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
};

class PriorityQueueTest {
private:
    class Node {
    public:
        int itemToCompare;
        pair<int, int> valueToStore;
        Node() : itemToCompare(INT_MIN) {}
        Node(int a, pair<int, int> b) : itemToCompare(a), valueToStore(b) {}
        string to_string() {
            return "{" + std::to_string(itemToCompare) + "," + "(" + std::to_string(valueToStore.first) + "," + std::to_string(valueToStore.second) + ")" + "}";
        }
    };
public:
    static void test() {
        cout << "Int test (Ascending)::" << endl;
        {
            PriorityQueue<int> pq;
            cout << "Current state of pq: ";
            while (!pq.empty()) {
                cout << pq.pop() << " ";
            }
            cout << endl;

            pq.add(314);
            pq.add(1);
            pq.add(234134);
            pq.add(2);
            pq.add(0);
            pq.add(10);
            pq.add(23425);
            pq.add(2000);

            cout << "Current state of pq: ";
            while (!pq.empty()) {
                cout << pq.pop() << " ";
            }
            cout << endl;
        }

        cout << "Int test (Descending)::" << endl;
        {
            auto comparator = [](const int& a, const int& b) {return a > b; };
            PriorityQueue<int> pq(comparator);
            cout << "Current state of pq: ";
            while (!pq.empty()) {
                cout << pq.pop() << " ";
            }
            cout << endl;

            pq.add(314);
            pq.add(1);
            pq.add(234134);
            pq.add(2);
            pq.add(0);
            pq.add(10);
            pq.add(23425);
            pq.add(2000);

            cout << "Current state of pq: ";
            while (!pq.empty()) {
                cout << pq.pop() << " ";
            }
            cout << endl;
        }

        cout << "Node test(Ascending) ::" << endl;
        {
            auto comparator = [](const Node& a, const Node& b) {return a.itemToCompare < b.itemToCompare; };
            PriorityQueue<Node> pq(comparator);
            pq.add(Node(50, { 3,4 }));
            pq.add(Node(10, { 3,4 }));
            pq.add(Node(500, { 3,4 }));
            pq.add(Node(50, { 3,4 }));
            pq.add(Node(10, { 3,4 }));
            pq.add(Node(5, { 3,4 }));
            while (!pq.empty()) {
                cout << pq.pop().to_string() << endl;
            }
        }

        cout << "Node test(Descending) ::" << endl;
        {
            auto comparator = [](const Node& a, const Node& b) {return a.itemToCompare > b.itemToCompare; };
            PriorityQueue<Node> pq(comparator);
            pq.add(Node(50, { 3,4 }));
            pq.add(Node(10, { 3,4 }));
            pq.add(Node(500, { 3,4 }));
            pq.add(Node(50, { 3,4 }));
            pq.add(Node(10, { 3,4 }));
            pq.add(Node(5, { 3,4 }));
            while (!pq.empty()) {
                cout << pq.pop().to_string() << endl;
            }
        }
    }
};