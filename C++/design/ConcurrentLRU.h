#pragma once
#include <thread>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <cassert>
using namespace std;

using KEY = string;
using VALUE = string;
using DataSource = unordered_map<KEY, VALUE>;

template <class K, class V>
class Node
{
public:
    K key;
    V val;
    Node* prev, * next;
    Node(K key, V val) : key(key), val(val), prev(nullptr), next(nullptr) {}
};

template <class K, class V>
class LinkedList
{
private:
    Node<K, V>* head = nullptr;
    Node<K, V>* tail = nullptr;
public:
    void insert(Node<K, V>* node)
    {
        if (head == nullptr) {
            head = tail = node;
        }
        else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    Node<K, V>* evict()
    {
        if (head == nullptr || tail == nullptr) return head;
        auto rear = tail;
        cout << "Evicting {" << rear->key << ", " << rear->val << "}." << endl;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;

        return rear;
    }

    void moveToFront(Node<K, V>* node)
    {
        if (node == nullptr) return;
        cout << "Moving {" << node->key << ", " << node->val << "} to front." << endl;
        Node<K, V>* prev = node->prev;
        Node<K, V>* next = node->next;

        if (prev != nullptr) prev->next = next;
        if (next != nullptr) next->prev = prev;
        else tail = prev;

        node->next = head;
        head = node;
    }

    Node<K, V>* getRoot()
    {
        return head;
    }
};

template <class K, class V>
class ConcurrentLRU
{
    int sz = 0;
    int capacity = 0;
    unordered_map<K, Node<K, V>*> map;
    LinkedList<K, V> list;
    int inserts = 0, hits = 0, misses = 0, evicts = 0;

public:
    ConcurrentLRU(int capacity) : capacity(capacity) {}
    void put(K key, V val)
    {
        if (map.find(key) != map.end()) {
            cout << "Already exist {" << key << ", " << val << "}." << endl;
            return;
        }

        cout << "Put {" << key << ", " << val << "}" << endl;
        Node<K, V>* v = new Node<K, V>(key, val);
        if (sz >= capacity) {
            auto res = list.evict(); sz--;
            map.erase(res->key);
            delete res;
            evicts++;
        }

        map.insert({ key, v });
        list.insert(v);
        inserts++;
        sz++;
    }

    V get(K key)
    {
        V val;
        if (map.find(key) == map.end()) {
            cout << "Get {" << key << "} not found!!" << endl;
            misses++;
            return val;
        }
        auto node = map[key];

        val = node->val;
        cout << "Get {" << key << ", " << val << "}" << endl;
        hits++;

        return val;
    }

    tuple<int, int, int, int> metrics()
    {
        return { hits, misses, inserts, evicts };
    }
};

class ThreadPool
{
};

class ConcurrentLRUTester
{
private:
    ConcurrentLRU<KEY, VALUE>* lru = nullptr;

public:
    ConcurrentLRUTester(int lruSize, DataSource& in, DataSource& out) {
        lru = new ConcurrentLRU<KEY, VALUE>(lruSize);
    }

    void put()
    {
    }

    void get()
    {
    }
};

class Test
{
private:
    ConcurrentLRU<string, string>* lru = nullptr;

public:
    Test() {
        lru = new ConcurrentLRU<string, string>(10);
    }
    void test()
    {
        insertAndValidate({ 1, 10 }, { 0,0,10,0 });
        insertAndValidate({ 6, 15 }, { 0,0,15,5 });
        fetchAndValidate({ 1,20 }, { 6,15 }, { 10,10,15, 5 });
    }

    void insertAndValidate(tuple<int, int> range, tuple<int, int, int, int> expect)
    {
        for (int i = get<0>(range); i <= get<1>(range); i++) {
            string key = "key" + to_string(i);
            string val = "val" + to_string(i);
            lru->put(key, val);
        }
        auto res = lru->metrics();
        assert(get<0>(res) == get<0>(expect));
        assert(get<1>(res) == get<1>(expect));
        assert(get<2>(res) == get<2>(expect));
        assert(get<3>(res) == get<3>(expect));
    }

    void fetchAndValidate(tuple<int, int> accessRange, tuple<int, int> presentRange, tuple<int, int, int, int> expect)
    {
        int l = get<0>(presentRange);
        int r = get<1>(presentRange);
        for (int i = get<0>(accessRange); i <= get<1>(accessRange); i++) {
            string key = "key" + to_string(i);
            string val = "val" + to_string(i);
            auto res = lru->get(key);
            if (i >= l && i <= r) assert(val == res);
        }

        auto res = lru->metrics();
        assert(get<0>(res) == get<0>(expect));
        assert(get<1>(res) == get<1>(expect));
        assert(get<2>(res) == get<2>(expect));
        assert(get<3>(res) == get<3>(expect));
    }
};