#pragma once
#include "../header.h"

class SpecialStackWithAccessToMiddleElement {
    template <class T>
    class SpecialStackWithAccessToMiddleElementWithSTLStack {
        list<T>elements;
        list<T>::iterator middle = elements.end();

    public:
        void push(int elem) {
            elements.push_back(elem);
            if (elements.size() == 1) middle = elements.begin();
            else if (elements.size() % 2 == 1) middle++;
        }

        T pop() {
            if (elements.empty()) throw exception("stack is empty");

            auto last = elements.back();
            elements.pop_back();

            if (elements.empty()) middle = elements.end();
            else if (elements.size() % 2 == 0) middle--;

            return last;
        }

        T top() {
            if (elements.empty()) throw exception("stack is empty");

            return elements.back();
        }

        T getMid() {
            if (middle == elements.end()) throw exception("No middle element");

            return *middle;
        }

        bool empty() {
            return elements.empty();
        }

        int size() {
            return elements.size();
        }

        void deleteMid() {
            if (middle == elements.end()) throw exception("No middle element");
            auto middlePrev = middle; middlePrev--;
            elements.erase(middle); // middle becomes invalid after erase

            middle = middlePrev; // update middle with middle prev
            if (elements.empty()) middle = elements.end();
            if (elements.size() % 2 == 1) middle++;
        }
    };

    template <class T>
    class SpecialStackWithAccessToMiddleElementWithCustomLinkedList
    {
        class LinkedList {
            LinkedListNode<T>* head = nullptr;
            LinkedListNode<T>* middle = nullptr;

        public:
            int size = 0;

            void push_back(T elem) {
                if (head == nullptr) head = middle = new LinkedListNode<T>(elem);
                else {
                    head->next = new LinkedListNode<T>(elem);
                    head->next->prev = head;
                    head = head->next;

                    if (size % 2 == 0) middle = middle->next;
                }
                size++;
            }

            T back() {
                if (head == nullptr) throw exception("List is empty");
                return head->val;
            }

            T pop_back() {
                if (head == nullptr) throw exception("List is empty");
                auto last = head->val;
                head = head->prev;

                size--;

                if (head == nullptr) middle = nullptr;
                else if (size % 2 == 0) middle = middle->prev;

                return last;
            }

            T getMid() {
                if (middle == nullptr) throw exception("Invalid middle pointer");

                return middle->val;
            }

            void deleteMid() {
                if (middle == nullptr) throw exception("Invalid middle pointer");

                auto oldMiddle = middle;
                if (middle->prev) {
                    middle->prev->next = middle->next;
                    middle->next->prev = middle->prev;
                    middle = middle->prev;
                }
                else middle = middle->next;
                delete oldMiddle;

                size--;

                if (middle && (size % 2 == 1)) middle = middle->next;
            }

            bool empty() {
                return size == 0;
            }
        };

        LinkedList elements;
    public:
        void push(T elem) {
            elements.push_back(elem);
        }

        T top() {
            return elements.back();
        }

        T pop() {
            return elements.pop_back();
        }

        T getMid() {
            return elements.getMid();;
        }

        void deleteMid() {
            elements.deleteMid();
        }

        bool empty() {
            return elements.empty();
        }

        int size() {
            return elements.size;
        }
    };

public:
    static void test() {
        SpecialStackWithAccessToMiddleElementWithCustomLinkedList<int> st;
        auto add = [&st](auto elem) mutable {
            cout << "Pushing elem: " << elem << endl;
            st.push(elem);
            return true;
        };
        auto pop = [&st]() mutable {
            return st.pop();
        };
        auto mid = [&st]() mutable {
            cout << "Mid element: " << st.getMid() << endl;
            return st.getMid();
        };
        auto delMid = [&st]() mutable {
            cout << "Deleting Mid element: " << st.getMid() << endl;
            st.deleteMid();
            return true;
        };
        auto print = [&st]() mutable {
            cout << "Current state of stack: ";
            while (!st.empty()) cout << st.pop() << " ";
            cout << endl;
        };

        assert(add(1));
        assert(mid() == 1);
        assert(add(2));
        assert(mid() == 1);
        assert(add(3));
        assert(mid() == 2);

        assert(delMid());
        assert(mid() == 1);

        assert(st.size() == 2);
        print();
        assert(st.size() == 0);

        assert(add(1));
        assert(mid() == 1);
        assert(add(2));
        assert(mid() == 1);
        assert(add(3));
        assert(mid() == 2);
        assert(add(4));
        assert(mid() == 2);
        assert(add(5));
        assert(mid() == 3);
        assert(add(6));
        assert(mid() == 3);
        assert(add(7));
        assert(mid() == 4);
        assert(add(8));
        assert(mid() == 4);
        assert(add(9));
        assert(mid() == 5);
        assert(st.size() == 9);

        assert(delMid());
        assert(st.size() == 8);
        assert(mid() == 4);

        assert(delMid());
        assert(st.size() == 7);
        assert(mid() == 6);

        assert(delMid());
        assert(st.size() == 6);
        assert(mid() == 3);

        assert(delMid());
        assert(st.size() == 5);
        assert(mid() == 7);

        assert(pop() == 9);
        assert(st.size() == 4);
        assert(mid() == 2);

        assert(delMid());
        assert(st.size() == 3);
        assert(mid() == 7);

        print();
    }
};
