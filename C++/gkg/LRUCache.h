#pragma once
#include "../Header.h"

class LRUCache
{
private:
    unordered_map<int, list<pair<int, int>>::iterator> map;
    list<pair<int, int>> l;
    int capacity;
    int size;
public:
    //Constructor for initializing the cache capacity with the given value.
    LRUCache(int cap)
    {
        capacity = cap;
        size = 0;
    }

    static void test() {
        LRUCache obj(3);
        obj.set(1, 1);
        obj.set(2, 2);
        obj.set(3, 3);
        obj.set(4, 4);
        obj.set(5, 5);
        obj.set(6, 6);

        cout << obj.get(0) << endl;
        cout << obj.get(1) << endl;
        cout << obj.get(2) << endl;
        cout << obj.get(3) << endl;
        cout << obj.get(4) << endl;
        cout << obj.get(5) << endl;
        cout << obj.get(6) << endl;
        cout << obj.get(7) << endl;
    }

    //Function to return value corresponding to the key.
    int get(int key)
    {
        if (map.find(key) == map.end()) return -1;

        auto p = map[key];
        auto val = p->second;
        l.erase(p);

        l.push_front({ key, val });
        map[key] = l.begin();

        return val;
    }

    //Function for storing key-value pair.
    void set(int key, int value)
    {
        if (map.find(key) != map.end() || size == capacity) {
            if (map.find(key) != map.end()) {
                l.erase(map[key]);
            }
            else {
                auto v = l.back(); l.pop_back();
                map.erase(v.first);
            }
            size--;
        }

        l.push_front({ key,value });
        map[key] = l.begin();
        size++;
    }
};