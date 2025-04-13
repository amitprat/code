// File: is_linked_list_palin.cpp
#pragma once
#include <chrono>
#include <concepts>
#include <deque>
#include <iostream>
#include <memory>
#include <stack>

#include "LinkedList.h"

template <typename T>
concept EqualityComparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
};

template <EqualityComparable T>
class IsLinkedListPalin {
    using Node = typename LinkedList<T>::Node;
    using Clock = std::chrono::high_resolution_clock;

   public:
    static void test() {
        IsLinkedListPalin obj;

        const std::vector<std::vector<T>> test_cases = {
            {}, {1}, {1, 1}, {1, 2}, {1, 2, 1}, {1, 2, 2, 1}, {1, 2, 2, 1, 3}, std::vector<T>(1'000, 1), [] { std::vector<T> v(500, 1); v.push_back(0); v.insert(v.end(), 500, 1); return v; }()};

        for (const auto& vals : test_cases) {
            LinkedList<T> list(vals);
            std::cout << "\nList: " << list.to_string().substr(0, 100) << (list.to_string().size() > 100 ? "..." : "") << std::endl;
            benchmark(list, obj);
        }
    }

    static void benchmark(const LinkedList<T>& list, IsLinkedListPalin& obj) {
        auto run = [&](auto&& method, const std::string& name) {
            auto start = Clock::now();
            bool result = method();
            auto end = Clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << name << ": result=" << result << ", time=" << elapsed.count() << "ms\n";
        };

        run([&] { return obj.isPalinStack(list); }, "Stack");
        run([&] { return obj.isPalinDeque(list); }, "Deque");
        run([&] { return obj.isPalinReverseClone(list); }, "ReverseClone");
        run([&] { return obj.isPalinRecursiveWrapper(list); }, "Recursive");
        run([&] { return obj.isPalindromeEfficientChecked(list); }, "Efficient(O1Space)");
    }

   public:
    bool isPalinStack(const LinkedList<T>& list) {
        std::stack<Node*> st;
        Node* slow = list.getHead();
        Node* fast = list.getHead();

        while (fast && fast->next) {
            st.push(slow);
            slow = slow->next;
            fast = fast->next->next;
        }
        if (fast) slow = slow->next;

        while (slow) {
            if (st.empty() || st.top()->val != slow->val) return false;
            st.pop();
            slow = slow->next;
        }
        return st.empty();
    }

   public:
    bool isPalinDeque(const LinkedList<T>& list) {
        std::deque<T> dq;
        for (Node* node = list.getHead(); node; node = node->next) {
            dq.push_back(node->val);
        }

        while (dq.size() > 1) {
            if (dq.front() != dq.back()) return false;
            dq.pop_front();
            dq.pop_back();
        }
        return true;
    }

   public:
    bool isPalinReverseClone(const LinkedList<T>& list) {
        Node* start = list.getHead();
        Node* end(reverseClone(start));
        while (start && end) {
            if (start->val != end->val) return false;
            start = start->next;
            end = end->next;
        }
        return true;
    }

    Node* reverseClone(Node* node) {
        Node* prev = nullptr;
        while (node) {
            auto* clone = new Node(node->val);
            clone->next = prev;
            prev = clone;
            node = node->next;
        }
        return prev;
    }

   public:
    bool isPalinRecursiveWrapper(const LinkedList<T>& list) {
        Node* node = list.getHead();
        return isPalinRecursive(node, node);
    }

    bool isPalinRecursive(Node*& start, Node* end) {
        if (!end) return true;
        bool res = isPalinRecursive(start, end->next);
        if (!res || (start->val != end->val)) return false;
        start = start->next;
        return true;
    }

   public:
    bool isPalindromeEfficientChecked(const LinkedList<T>& list) {
        std::string before = list.to_string();
        bool result = isPalindromeEfficient(list);
        std::string after = list.to_string();
        if (before != after) throw std::runtime_error("List modified in isPalindromeEfficient");
        return result;
    }

    bool isPalindromeEfficient(const LinkedList<T>& list) {
        Node* head = list.getHead();
        if (!head || !head->next) return true;

        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* secondHalf = reverse(slow);
        Node* copySecondHalf = secondHalf;

        Node* firstHalf = head;
        bool result = true;
        while (secondHalf) {
            if (firstHalf->val != secondHalf->val) {
                result = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }

        reverse(copySecondHalf);
        return result;
    }

   private:
    Node* reverse(Node* head) {
        Node* prev = nullptr;
        while (head) {
            Node* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};
