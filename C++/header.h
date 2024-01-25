#pragma once

#include <ctype.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std::views;
using namespace std;

#include "ds/Tree.h"

// template <typename T>
// void print(string text = "", const vector<T> &arr = {})
// {
//     if (!text.empty())
//         cout << text << " : ";
//     std::ranges::copy(path, std::ostream_iterator<char>(std::cout, " "));
//     cout << endl;
// }

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::ranges::copy(v, std::ostream_iterator<T>(out, ", "));
        out << "]";
        // out << '\b' << '\b' << ']';  // use two ANSI backspace characters '\b' to overwrite final ", "
    }
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<pair<T, T>> &arr) {
    for (auto &val : arr) {
        out << val << ", ";
    }

    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const pair<T, T> &v) {
    out << "{" << v.first << "," << v.second << "}";
    return out;
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const map<U, V> &v) {
    out << "[";
    bool prev = false;
    for (auto &e : v) {
        if (prev)
            out << ", ";
        out << "{" << e.first << "," << e.second << "}";

        prev = true;
    }
    out << "]";

    return out;
}

std::ostream &operator<<(std::ostream &out, Tree::Node *root) {
    Tree::prettyPrintTree(root, out);
    return out;
}

template <typename U, typename V>
std::ostream &operator<<(std::ostream &out, const unordered_map<U, V> &v) {
    if (!v.empty()) {
        out << '[';
        for (auto &p : v) {
            out << "{" << p.first << ":" << p.second << "}, ";
        }
        out << ']';
    }
    return out;
}

template <class T>
std::ostream &operator<<(std::ostream &out, vector<vector<T>> &matrix) {
    int N = matrix.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            out << matrix[i][j] << "\t";
        cout << endl;
    }

    return out;
}

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

#define START_METHOD() \
    auto startTime = chrono::high_resolution_clock::now();

#define END_METHOD()                                              \
    auto endTime = chrono::high_resolution_clock::now();          \
    std::chrono::duration<double> duration = endTime - startTime; \
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
};

struct Interval {
    int start = 0, end = 0;
    string to_string() {
        stringstream ss;
        ss << "{" << start << "," << end << "}";
        return ss.str();
    }

    bool operator==(const Interval &that) {
        return this->start == that.start && this->end == that.end;
    }
};

template <typename T>
string to_string(vector<T> arr) {
    stringstream ss;
    ss << "[";
    for (auto &e : arr) {
        ss << e << ",";
    }
    ss.seekp(-1, std::ios_base::end);
    ss << "]";

    return ss.str();
}

template <typename T>
string to_string(pair<T, T> p) {
    stringstream ss;
    ss << "[";
    ss << p.first << "," << p.second;
    ss << "]";

    return ss.str();
}

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
        for (auto &e : arr) {
            head->next = new ListNode(e);
            head = head->next;
        }

        auto next = head->next;
        delete head;

        return next;
    }

    static int length(ListNode *head) {
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

// void logError(std::string_view errorMessage,
//               std::source_location location = std::source_location::current()) {
//     std::println("{}:{}:{} - An unexpected error occurred in {}: {}",
//                  location.file_name(), location.line(), location.column(),
//                  location.function_name(), errorMessage);
// }