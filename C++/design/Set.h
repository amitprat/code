#pragma once
#include "../header.h"

template <class T>
class Set : unordered_set<T>
{
public:
    bool add(T val) {
        return this->insert(val).second;
    }
    bool exists(T val) {
        return this->find(val) != this->end();
    }
    bool remove(T val) {
        if (!exists(val)) return false;
        this->erase(val);
        return true;
    }
    string to_string() {
        stringstream ss;
        for (auto& n : *this) {
            ss << n << ", ";
        }
        ss.seekp(-2, std::ios_base::end);
        ss << '\0';
        return ss.str();
    }
};

template <class T>
class TreeSet : set<T>
{
public:
    bool add(T val) {
        return this->insert(val).second;
    }
    bool exists(T val) {
        return this->find(val) != this->end();
    }
    bool remove(T val) {
        if (!exists(val)) return false;
        this->erase(val);
        return true;
    }
    string to_string() {
        stringstream ss;
        for (auto& n : *this) {
            ss << n << ", ";
        }
        ss.seekp(-2, std::ios_base::end);
        ss << '\0';
        return ss.str();
    }
};

class SetTest {
public:
    static void test() {
        Set<int> obj;
        cout << obj.exists(1) << endl;
        obj.add(1);
        obj.add(2);
        cout << obj.exists(2) << endl;
        cout << obj.to_string() << endl;
    }
};