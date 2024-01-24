#pragma once
#include "../Header.h"

class Multimap {
public:
    static void test() {
        multimap<int, int> mmap;
        mmap.insert({ 1,40 });
        mmap.insert({ 2,30 });
        mmap.insert({ 3,60 });
        mmap.insert({ 6,50 });
        mmap.insert({ 6,10 });

        cout << "Map: " << endl;
        for (auto& entry : mmap) {
            cout << to_string(entry) << endl;
        }

        mmap.insert({ 4,50 });
        mmap.insert({ 5,10 });

        cout << "Map: " << endl;
        for (auto& entry : mmap) {
            cout << to_string(entry) << endl;
        }

        mmap.erase(4);
        cout << "Map: " << endl;
        for (auto& entry : mmap) {
            cout << to_string(entry) << endl;
        }

        mmap.erase(5);
        cout << "Map: " << endl;
        for (auto& entry : mmap) {
            cout << to_string(entry) << endl;
        }

        cout << "Lower bound:" << endl;
        auto iter = mmap.lower_bound(6);
        cout << iter->first << ", " << iter->second << endl;

        cout << "Upper bound:" << endl;
        auto iter1 = mmap.upper_bound(6);
        cout << iter1->first << ", " << iter1->second << endl;

        cout << "Equal range:" << endl;
        auto iter2 = mmap.equal_range(6);
        for (auto s = iter2.first; s != iter2.second; s++) {
            cout << s->first << ", " << s->second << endl;
        }

        cout << "total elements for 6 " << distance(iter2.first, iter2.second) << endl;

        cout << "Equal range:" << endl;
        auto iter3 = mmap.equal_range(7);
        auto cnt = distance(iter3.first, iter3.second);
        cout << "total elements for 7 " << cnt << endl;
    }
};