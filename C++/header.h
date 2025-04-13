#pragma once

#include <algorithm>
#include <any>
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
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <ranges>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ds/Graph.h"
#include "linkedlist/LinkedList.h"
#include "tree/BinaryTree.h"

using namespace std;
using namespace std::views;

// Logging utilities
template <typename... Args>
void trace(std::string_view label, Args&&... args) {
    std::cerr << "[TRACE] " << label << ": ";
    ((std::cerr << args << " "), ...);
    std::cerr << std::endl;
}

inline void traceLine(std::string_view msg = "") {
    std::cerr << "[------] " << msg << std::endl;
}

inline void traceHeader(std::string_view msg) {
    std::cerr << "\n========= " << msg << " =========\n";
}

// Timer for benchmarking
class ScopedTimer {
   public:
    explicit ScopedTimer(std::string name = "") : name(std::move(name)), start(chrono::high_resolution_clock::now()) {}
    ~ScopedTimer() {
        const auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        std::cerr << format("[TIMER] {} took {:.6f} seconds\n", name, duration.count());
    }

   private:
    std::string name;
    chrono::high_resolution_clock::time_point start;
};

// Overload ostream << for vector
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << '[';
    for (size_t i = 0; i < v.size(); ++i)
        out << v[i] << (i + 1 < v.size() ? ", " : "");
    return out << ']';
}

// Overload ostream << for vector<pair<T, T>>
template <typename T>
ostream& operator<<(ostream& out, const vector<pair<T, T>>& arr) {
    out << '[';
    for (size_t i = 0; i < arr.size(); ++i)
        out << arr[i] << (i + 1 < arr.size() ? ", " : "");
    return out << ']';
}

template <typename U, typename V>
ostream& operator<<(ostream& out, const pair<U, V>& p) {
    return out << format("{{{}, {}}}", p.first, p.second);
}

template <typename U, typename V>
ostream& operator<<(ostream& out, const vector<pair<U, V>>& arr) {
    out << '[';
    for (size_t i = 0; i < arr.size(); ++i)
        out << arr[i] << (i + 1 < arr.size() ? ", " : "");
    return out << ']';
}

template <typename T>
string to_string(const vector<T>& v) {
    ostringstream ss;
    ss << v;
    return ss.str();
}

template <typename T>
ostream& operator<<(ostream& out, const pair<T, T>& p) {
    return out << format("{{{}, {}}}", p.first, p.second);
}

template <typename T>
string to_string(const pair<T, T>& p) {
    return format("{{{}, {}}}", p.first, p.second);
}

template <typename U, typename V>
ostream& operator<<(ostream& out, const map<U, V>& m) {
    out << '[';
    for (auto it = m.begin(); it != m.end(); ++it)
        out << '(' << it->first << ", " << it->second << ')' << (next(it) != m.end() ? ", " : "");
    return out << ']';
}

template <typename U, typename V>
ostream& operator<<(ostream& out, const unordered_map<U, V>& m) {
    out << '[';
    for (const auto& [k, v] : m)
        out << '(' << k << ", " << v << "), ";
    if (!m.empty()) out.seekp(-2, ios_base::end);
    return out << ']';
}

template <typename T>
ostream& operator<<(ostream& out, const unordered_set<T>& s) {
    out << '[';
    for (const auto& e : s)
        out << e << ", ";
    if (!s.empty()) out.seekp(-2, ios_base::end);
    return out << ']';
}

template <typename T>
string to_string(const unordered_set<T>& s) {
    ostringstream ss;
    ss << s;
    return ss.str();
}

template <typename T>
ostream& operator<<(ostream& out, const set<T>& s) {
    out << '[';
    for (auto it = s.begin(); it != s.end(); ++it)
        out << *it << (next(it) != s.end() ? ", " : "");
    return out << ']';
}

template <typename T>
string to_string(const set<T>& s) {
    return to_string(vector<T>{s.begin(), s.end()});
}

template <typename T, size_t N>
ostream& operator<<(ostream& out, const array<T, N>& a) {
    out << '[';
    for (size_t i = 0; i < a.size(); ++i)
        out << a[i] << (i + 1 < a.size() ? ", " : "");
    return out << ']';
}

template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& matrix) {
    for (const auto& row : matrix) out << row << '\n';
    return out;
}

struct Point {
    int x{}, y{};

    constexpr Point(int x = 0, int y = 0) : x(x), y(y) {}

    friend ostream& operator<<(ostream& out, const Point& p) {
        return out << format("{{{}, {}}}", p.x, p.y);
    }

    bool operator==(const Point&) const = default;
    Point operator+(const Point& other) const { return {x + other.x, y + other.y}; }
};

struct Interval {
    int start{}, end{};

    constexpr Interval(int s = 0, int e = 0) : start(s), end(e) {}

    friend ostream& operator<<(ostream& out, const Interval& i) {
        return out << format("{{{}, {}}}", i.start, i.end);
    }

    bool operator==(const Interval&) const = default;
};

template <typename T>
bool areEqual(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) {
        trace("Size Mismatch", a.size(), "vs", b.size());
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (!(a[i] == b[i])) {
            trace("Element Mismatch", "index", i, a[i], "!=", b[i]);
            return false;
        }
    }
    return true;
}

template <typename T>
bool areEqual(const typename LinkedList<T>::Node* a, const typename LinkedList<T>::Node* b) {
    const auto lenA = LinkedList<T>::length(a);
    const auto lenB = LinkedList<T>::length(b);

    if (lenA != lenB) {
        trace("List length mismatch", lenA, "vs", lenB);
        return false;
    }
    for (; a && b; a = a->next, b = b->next) {
        if (a->val != b->val) {
            trace("List node mismatch", a->val, "!=", b->val);
            return false;
        }
    }
    return true;
}
