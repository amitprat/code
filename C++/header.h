#pragma once
#include <ctype.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <concepts>
#include <condition_variable>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std::views;
using namespace std;

/*----------------------Overload ostream << operators------------------------------------*/
template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(out, ", "));
        out << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }
    return out;
}

template <typename T>
string to_string(const vector<T> &v) {
    stringstream ss;
    if (!v.empty()) {
        ss << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(ss, ", "));
        ss << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }

    return ss.str();
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<pair<T, T>> &arr) {
    if (!arr.empty()) {
        out << "[";
        for (auto &val : arr) {
            out << val << ", ";
        }
        out << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }

    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const pair<T, T> &v) {
    out << "{" << v.first << ", " << v.second << "}";
    return out;
}

template <typename T>
std::string to_string(const pair<T, T> &v) {
    stringstream ss;
    ss << "{" << v.first << ", " << v.second << "}";
    return ss.str();
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const map<U, V> &v) {
    if (!v.empty()) {
        out << "[";
        for (auto &e : v) out << "(" << e.first << ", " << e.second << ")";
        out << '\b' << '\b' << ']';
    }

    return out;
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const unordered_map<U, V> &v) {
    if (!v.empty()) {
        out << "[";
        for (auto &e : v) out << "(" << e.first << ", " << e.second << ")";
        out << '\b' << '\b' << ']';
    }

    return out;
}

template <typename U>
std::ostream &operator<<(std::ostream &out, const unordered_set<U> &v) {
    if (!v.empty()) {
        out << "[";
        for (auto &e : v) out << e << ", ";
        out << '\b' << '\b' << ']';
    }

    return out;
}

template <typename T>
string to_string(const unordered_set<T> &v) {
    stringstream ss;
    if (!v.empty()) {
        ss << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(ss, ", "));
        ss << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }

    return ss.str();
}

template <typename U>
std::ostream &operator<<(std::ostream &out, const set<U> &v) {
    if (!v.empty()) {
        out << "[";
        for (auto &e : v) out << e.first << ", ";
        out << '\b' << '\b' << ']';
    }

    return out;
}

template <typename T>
string to_string(const set<T> &v) {
    stringstream ss;
    if (!v.empty()) {
        ss << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(ss, ", "));
        ss << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }

    return ss.str();
}

template <typename U, std::size_t N>
std::ostream &operator<<(std::ostream &out, const array<U, N> &v) {
    if (!v.empty()) {
        out << "[";
        for (auto &e : v) out << e << ", ";
        out << '\b' << '\b' << ']';
    }

    return out;
}

template <class T>
std::ostream &operator<<(std::ostream &out, vector<vector<T>> &matrix) {
    int N = matrix.size();
    if (N > 0) {
        for (int i = 0; i < N; i++) {
            out << matrix[i] << endl;
        }
    }

    return out;
}

// std::ostream &operator<<(std::ostream &out, Tree::Node *root) {
//     Tree::prettyPrintTree(root, out);
//     return out;
// }
/*----------------------Overload ostream << operators------------------------------------*/

/*----------------------Common Data structures------------------------------------*/
struct Point {
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    string to_string() const {
        stringstream ss;
        ss << "{" << x << "," << y << "}";

        return ss.str();
    }

    bool operator==(const Point &that) {
        return this->x == that.x && this->y == that.y;
    }

    bool operator!=(const Point &that) {
        return (this->x != that.x || this->y != that.y);
    }

    Point operator+(const Point &that) {
        Point newPoint;
        newPoint.x = this->x + that.x;
        newPoint.y = this->y + that.y;

        return newPoint;
    }

    friend ostream &operator<<(ostream &out, const Point &p) {
        out << p.to_string();
        return out;
    }
};

struct Interval {
    int start = 0, end = 0;
    string to_string() const {
        stringstream ss;
        ss << "{" << start << "," << end << "}";
        return ss.str();
    }

    bool operator==(const Interval &that) {
        return this->start == that.start && this->end == that.end;
    }

    friend ostream &operator<<(ostream &out, const Interval &it) {
        out << it.to_string();

        return out;
    }
};

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    string to_string() {
        return std::to_string(val);
    }
};

struct ListNode {
    int val;
    ListNode *prev, *next;
    ListNode(int val) : val(val), prev(nullptr), next(nullptr) {}
    string to_string() {
        return std::to_string(val);
    }

    static ListNode *create(const vector<int> &arr) {
        ListNode *head = new ListNode(-1);  // dummy
        ListNode *tail = head;
        for (auto &e : arr) {
            tail->next = new ListNode(e);
            tail = tail->next;
        }

        auto next = head->next;
        delete head;

        return next;
    }

    static int length(const ListNode *head) {
        int sz = 0;
        while (head) {
            sz++;
            head = head->next;
        }

        return sz;
    }
};

ostream &operator<<(ostream &out, ListNode *head) {
    out << "{";
    while (head) {
        out << head->to_string() << ", ";
        head = head->next;
    }
    out << "}";

    return out;
}
/*----------------------Common Data structures------------------------------------*/

/*----------------------Common Assert operations start------------------------------------*/
template <typename T>
bool areEqual(const vector<T> &arr1, const vector<T> &arr2) {
    if (arr1.size() != arr2.size()) {
        cerr << "array size mismatch, arr1 size: " << arr1.size() << ", arr2 size: " << arr2.size() << endl;
        return false;
    }

    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i] != arr2[i]) {
            cerr << "element mismatch, arr1[i]:" << arr1[i] << ", arr2[i]:" << arr2[i] << endl;
            return false;
        }
    }

    return true;
}

bool areEqual(const ListNode* first, const ListNode* second) {
    if(!first && !second) return true;
    if(!first || !second) {
        cerr << "One of specified list is null!"<<endl;
        return false;
    }
    if(ListNode::length(first) != ListNode::length(second)) {
        cerr <<format("Length of first list {} != {} length of second list.", ListNode::length(first), ListNode::length(second))<<endl;
        return false;
    }

    const ListNode *tmpFirstRoot = first;
    const ListNode *tmpSecondRoot = second;

    while(tmpFirstRoot) {
        if(tmpFirstRoot->val != tmpSecondRoot->val) {
            cerr<<format("(List node value from first list) {} != {} (node value from second list).", tmpFirstRoot->val, tmpSecondRoot->val)<<endl;
            return false;
        }

        tmpFirstRoot = tmpFirstRoot->next;
        tmpSecondRoot = tmpSecondRoot->next;
    }

    return true;
}
/*----------------------Common Assert operations end--------------------------------------*/

//-----------------------------------------unused---------------------------------------------------------
#define START_METHOD() \
    auto startTime = chrono::high_resolution_clock::now();

#define END_METHOD()                                              \
    auto endTime = chrono::high_resolution_clock::now();          \
    std::chrono::duration<double> duration = endTime - startTime; \
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

// void logError(std::string_view errorMessage,
//               std::source_location location = std::source_location::current()) {
//     std::println("{}:{}:{} - An unexpected error occurred in {}: {}",
//                  location.file_name(), location.line(), location.column(),
//                  location.function_name(), errorMessage);
// }
//-----------------------------------------unused---------------------------------------------------------