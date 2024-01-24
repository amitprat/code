#pragma once
#include "../Header.h"

class MRUCache {
private:
    class Node {
        string key;
        string val;
        Node() {}
        Node(string key, string val):key(key),val(val) {}
    };
    int capacity = 0;
    int size = 0;
    unordered_map<string, list<Node>::iterator> map;
    list<Node> list;

public:
    static void test() {
        MRUCache obj(10);
        srand(time(nullptr));
        for (int i = 0; i < 30; i++) {
            string key = "key-" + to_string(i);
            string val = "val-" + to_string(i);
            obj.put(key, val);

            if (rand() % 2 == 0) {
                cout << "Get for key " + key + " = " + obj.get(key) << endl;
            }
        }
    }

    MRUCache(int capacity):capacity(capacity),size(0) {}

    void put(string key, string val) {

        size++;
    }

    string get(string key) {
        if (!exists(key)) throw exception(string("Key: " + key + " not found in cahce."));
    }

private:
    bool exists(string key) {
        return map.find(key) == map.end();
    }

    bool isFull() {
        return size == capacity;
    }
};