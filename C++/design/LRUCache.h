#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> fsec;

template <class K, class V>
class LRUCache
{
    using E = pair<K, V>;
private:
    int capacity;
    list<E> dq;
    unordered_map<K, list<pair<int, int>>::iterator> map;
    ofstream out;
    ifstream in;
    string file;

public:
    LRUCache(int capacity) : capacity(capacity) {
        this->file = "D:/out.log";
        this->in.open(file);
    }

    static void test()
    {
        int capacity = 5;
        LRUCache<int, int> lru(capacity);
        lru.put(1, 100);
        lru.put(2, 200);
        lru.put(3, 300);
        lru.put(4, 400);
        lru.put(5, 500);
        lru.put(6, 600);
        cout << "Value for key 1:" << lru.get(1) << endl << endl;
        cout << "Value for key 2:" << lru.get(2) << endl;
        cout << "Value for key 3:" << lru.get(3) << endl;
        cout << "Value for key 5:" << lru.get(5) << endl;
        cout << "Value for key 6:" << lru.get(6) << endl;
        cout << "Value for key 7:" << lru.get(7) << endl;
        lru.put(3, 300);
        lru.put(4, 400);
        lru.put(5, 500);
        lru.put(6, 600);
        lru.put(1, 100);
        lru.put(7, 700);
        cout << "Value for key 1:" << lru.get(1) << endl;
        cout << "Value for key 2:" << lru.get(2) << endl;
        cout << "Value for key 3:" << lru.get(3) << endl;
        cout << "Value for key 4:" << lru.get(4) << endl;
        cout << "Value for key 5:" << lru.get(5) << endl;
        cout << "Value for key 6:" << lru.get(6) << endl;
        cout << "Value for key 7:" << lru.get(7) << endl;
    }

    void put(K key, V val)
    {
        cout << "Inserting: " << key << " " << val << endl;
        in.clear();
        auto currentState = readAll();
        if (currentState.find(to_string(key)) != currentState.end()) {
            currentState[to_string(key)] = to_string(val);
        }
        else {
            currentState.insert({ to_string(key), to_string(val) });
        }
        writeAll(currentState);
        in.clear();
    }

    V get(K key)
    {
        cout << "Getting for key: " << key << endl;
        if (map.find(key) == map.end()) {
            auto t0 = Time::now();
            cout << "Key " << key << " doesn't exist in cache, load from backend." << endl;
            E readValue;
            bool res = readFromFile(key, readValue);
            if (!res) {
                cout << "Key " << key << " doesn't exist data in backend store" << endl;
                return V();
            }
            dq.push_front(readValue);
            map[key] = dq.begin();
            auto t1 = Time::now();
            fsec fs = t1 - t0;
            ms d = std::chrono::duration_cast<ms>(fs);
            cout << "Value loaded from backend data in " << d.count() << "ms." << endl;
            return readValue.second;
        }

        auto t0 = Time::now();
        auto val = map[key]->second;
        dq.erase(map[key]);
        map.erase(key);

        dq.push_front({ key, val });
        map[key] = dq.begin();
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = std::chrono::duration_cast<ms>(fs);
        cout << "Value loaded from cache data in " << d.count() << "ms." << endl;

        return val;
    }

    bool readFromFile(K key, E& response)
    {
        string line;
        while (in >> line) {
            pair<string, string> parts = split(line, ':');
            if (stoi(parts.first) == key) {
                cout << "Found data in backend for key " << key << endl;
                response = { stoi(parts.first), stoi(parts.second) };
                return true;
            }
        }

        return false;
    }

    pair<string, string> split(string line, char ch)
    {
        size_t pos = line.find(ch);
        return { line.substr(0, pos), line.substr(pos + 1) };
    }

    unordered_map<string, string> readAll()
    {
        unordered_map<string, string> map;
        string line;
        while (in >> line) {
            pair<string, string> parts = split(line, ':');
            map.insert(parts);
        }

        return map;
    }

    void writeAll(unordered_map<string, string> currentState)
    {
        out.open(file, std::ofstream::out | std::ofstream::trunc);
        for (auto cur : currentState) {
            out << cur.first << ":" << cur.second << endl;
        }
        out.flush();
        out.close();
    }
};