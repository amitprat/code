#pragma once
#include "../Header.h"

template <typename K, typename V>
class DLL {
public:
    class Node {
    public:
        K key;
        V val;
        Node* prev;
        Node* next;
        Node(K key, V val) : key(key), val(val), prev(nullptr), next(nullptr) {}
        string to_string() {
            return std::string(key) + "," + std::to_string(val);
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    void push_back(K key, V val) {
        if (!head) head = tail = new Node(key, val);
        else {
            tail->next = new Node(key, val);
            tail->next->prev = tail;
        }
    }

    Node* push_front(K key, V val) {
        if (!head) head = tail = new Node(key, val);
        else {
            auto tmp = new Node(key, val);
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        return head;
    }

    K pop_back() {
        if (!head) throw exception("Empty!!");
        auto n = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        auto key = n->key;
        delete n;
        return key;
    }

    void moveToFront(Node* node) {
        if (node->prev) node->prev = node->next;
        if (node->next) node->next->prev = node->prev;
        node->next = head;
        head->prev = node;
        head = node;
    }
};

template <typename K, typename V>
class LRU {
    int capacity = 0;
    unordered_map<K, DLL<string, string>::Node*> map;
    DLL<K, V> dll;
public:
    LRU(int capacity) :capacity(capacity) {}
    static void test() {
        srand(time(NULL));
        int size = 5;
        LRU<string, string> lru(size);
        for (int i = 0; i < 10; i++) {
            try {
                int num = rand() % 10;
                string key = "key" + std::to_string(num);
                string val = "val" + std::to_string(num);

                lru.put(key, val);

                num = rand() % 10;
                key = "key" + std::to_string(num);
                auto res = lru.get(key);
                cout << "Get (" << key << ") = " << res << endl;
                cout << endl << endl;
            }
            catch (exception e) {
                cout << e.what() << endl;
            }
        }
    }

    bool put(K key, V val) {
        cout << "Put (" << key << "," << val << ")" << endl;
        if (exists(key)) {
            cout << "Alread exists!" << endl;
            return false;
        }

        if (isFull()) {
            cout << "Is Full, removing from back" << endl;
            removeFromBack();
        }
        cout << "Inserting at front";
        insertAtFront(key, val);

        return true;
    }

    V get(K key) {
        cout << "Get (" << key << ")" << endl;
        if (isEmpty()) throw exception("Empty!!");
        if (!exists(key)) throw exception("Key not found!!");

        return getAndMoveToFront(key);
    }

    bool exists(K key) {
        return map.find(key) != map.end();
    }

    bool isEmpty() {
        return map.empty();
    }

    V getAndMoveToFront(K key) {
        auto node = map[key];
        dll.moveToFront(node);

        return node->val;
    }

    void moveToFront(K key) {
        auto node = map[key];
        dll.moveToFront(node);
    }

    bool isFull() {
        return map.size() == capacity;
    }

    void removeFromBack() {
        auto key = dll.pop_back();
        map.erase(key);
    }
    void insertAtFront(K key, V val) {
        auto node = dll.push_front(key, val);
        map[key] = node;
    }
};