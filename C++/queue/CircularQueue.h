#pragma once
#include "../header.h"

namespace cq {
    template <class T>
    class CircularQueue {
    public:
        class Node {
        public:
            T val;
            Node* prev, * next;
            Node(T val) :val(val), prev(nullptr), next(nullptr) {}
        };
    private:
        Node* head, * tail;
        int sz = 0;
    public:
        CircularQueue() :head(nullptr), tail(nullptr) {}
        static void test() {
            CircularQueue<string> dq;
            auto pushd = [&dq](auto item) mutable {
                cout << "Pushing item = " << item << endl;
                dq.push(item);
            };
            auto popd = [&dq]() mutable {
                cout << "Popped item = " << dq.pop() << endl;
            };
            auto frontd = [&dq]() mutable {
                cout << "Front item = " << dq.front() << endl;
            };
            auto print = [&dq]() mutable {
                cout << "Queue State: ";
                while (!dq.empty()) {
                    cout << dq.pop() << " ";
                }
                cout << endl;
            };

            try {
                pushd("1");
                pushd("2");
                popd();
                pushd("3");
                pushd("4");
                pushd("5");
                pushd("6");
                popd();
                pushd("7");
                pushd("8");
                pushd("9");
                pushd("10");
                popd(); popd();
                print();
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
        }
        void push(T item) {
            if (head == nullptr) {
                head = tail = new Node(item);
            }
            else {
                tail->next = new Node(item);
                tail = tail->next;
                tail->next = head;
            }
            sz++;
        }
        T pop() {
            if (head == nullptr) throw exception("Queue is empty");
            if (head == tail) {
                auto val = head->val;
                delete head;
                head = tail = nullptr;
                sz--;
                return val;
            }

            auto f = head;
            head = head->next;
            tail->next = head;
            auto val = f->val;
            delete f;
            sz--;

            return val;
        }
        T front() {
            if (head == nullptr) throw exception("Queue is empty");
            return head->val;
        }
        bool empty() {
            return head == nullptr;
        }
        int size() {
            return sz;
        }
    };

    template <class T>
    class ArrayCircularQueue {
    private:
        T* arr = nullptr;
        int cap = 0;
        int start, end;
    public:
        ArrayCircularQueue(int cap) :cap(cap) {
            arr = new T[cap];
            start = end = 0;
        }
        static void test() {
            ArrayCircularQueue<string> cq(100);
            auto pushBackd = [&cq](auto item) mutable {
                try {
                    cout << "Push Back Item: " << item << endl;
                    cq.pushBack(item);
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };
            auto popBackd = [&cq]() mutable {
                try {
                    cout << "Pop Back Item: " << cq.popBack() << endl;
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };
            auto pushFrontd = [&cq](auto item) mutable {
                try {
                    cout << "Push Front Item: " << item << endl;
                    cq.pushFront(item);
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };
            auto popFrontd = [&cq]() mutable {
                try {
                    cout << "Pop Front Item: " << cq.popFront() << endl;
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };
            auto printBack = [&cq]() mutable {
                try {
                    cout << "Queue State: ";
                    while (!cq.empty()) cout << cq.popBack() << " ";
                    cout << endl;
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };
            auto printFwd = [&cq]() mutable {
                try {
                    cout << "Queue State: ";
                    while (!cq.empty()) cout << cq.popFront() << " ";
                    cout << endl;
                }
                catch (exception e) {
                    cout << e.what() << endl;
                }
            };

            popBackd();
            popBackd();
            popBackd();
            popBackd();
            popBackd();

            pushBackd("1");
            pushBackd("2");
            pushBackd("3");
            pushBackd("4");
            pushBackd("5");
            pushBackd("6");
            popBackd();
            pushBackd("7");
            pushBackd("8");
            pushBackd("9");
            pushBackd("10");

            popBackd();
            popBackd();
            popBackd();
            popBackd();
            popFrontd();
            popFrontd();
            popFrontd();
            popFrontd();
            popFrontd();
            popBackd();
            popBackd();
            popBackd();
            popFrontd();
            popFrontd();
            popFrontd();

            pushFrontd("0");
            pushFrontd("-1");
            pushFrontd("-2");
            popFrontd();
            pushFrontd("-3");
            pushFrontd("-4");
            pushFrontd("-5");
            pushFrontd("-6");
            popFrontd();
            pushFrontd("-7");
            popFrontd();
            popFrontd();
            pushFrontd("-8");
            pushFrontd("-9");

            popBackd();
            pushBackd("11");
            popBackd();
            popBackd();
            pushBackd("12");
            pushBackd("13");
            popBackd();
            pushBackd("14");
            popBackd();
            popBackd();
            popBackd();
            pushBackd("15");
            pushBackd("16");

            printFwd();
        }
        void pushBack(T item) {
            if (isFull()) throw exception("Queue is full");
            arr[end] = item;
            end = index(end + 1);
        }
        void pushFront(T item) {
            if (isFull()) throw exception("Queue is full");
            start = index(start - 1);
            arr[start] = item;
        }
        T popFront() {
            if (empty()) throw exception("Queue is empty");
            auto item = arr[start];
            start = index(start + 1);
            if (empty()) reset();

            return item;
        }
        T popBack() {
            if (empty()) throw exception("Queue is empty");
            end = index(end - 1);
            auto item = arr[end];

            if (empty()) reset();

            return item;
        }
        T front() {
            if (empty()) throw exception("Queue is empty");
            return arr[start];
        }
        T back() {
            if (empty()) throw exception("Queue is empty");
            return arr[end];
        }
        bool empty() {
            return start == end;
        }
        int size() {
            return (end + cap - start) % cap;
        }
        bool isFull() {
            return start == index(end + 1);
        }
        int index(int cur) {
            return (cur + cap) % cap;
        }
        void reset() {
            start = end = 0;
        }
    };
}