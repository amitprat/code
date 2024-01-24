#include "../header.h"

class LRUCache {
    class Database {
       public:
        unordered_map<int, int> map;
        Database() {
            for (int i = 0; i < 1000; i++) map[i] = i * 2;
        }
        int get(int key) { return map[key]; }
    };

    list<pair<int, int>> l;
    unordered_map<int, list<int, int>::iterator> map;

    int get(int key) {
        if (exists(key))
            return getAndMoveToFront(key);
        else {
            if (isFull()) removeFromBack();
            auto val = fetchFromDB(key);
            addToFront(key, val);
        }
    }

    bool exists(int key) { return map.find(key) != map.end(); }
    int getAndMoveToFront(int key) {
        auto it = map[key];
        int val = it->second;
        l.erase(it);
        l.push_front({key, val});

        return val;
    }

    int fetchFromDB(int key) {
        db.get(key);
    }

    void addToFront(int key, int val) {
        l.push_back({key, val});
        map[key] = l.begin();
    }

    bool isFull() {
        return map.size() == limit;
    }

    void removeFromBack() {
        auto it = l.back();
        l.pop_back();
        map.erase(it);
    }
};