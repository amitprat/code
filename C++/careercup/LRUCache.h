#pragma once
#include "../header.h"

namespace lrucache1 {
class LRUCache {
   public:
    static void test() {
        LRUCache cache(10);
        vector<int> keys = {5, 0, 1, 3, 2, 4, 1, 0, 5};
        srand(time(nullptr));

        for (auto key : keys) {
            try {
                auto v = cache.get(key);
                cout << "Fetched " << key << " = " << v << endl;
            } catch (exception e) {
                cout << e.what() << endl;
                cache.put(key, rand());
            }
        }
    }

   private:
    struct KeyValue {
        int key, value;
        KeyValue(int key, int value) : key(key), value(value) {}
        string to_string() { return "(" + std::to_string(key) + "," + std::to_string(value) + ")"; }
    };

    unordered_map<int, int> backendValues;

    int capacity = 0;
    list<KeyValue> dll;
    unordered_map<int, list<KeyValue>::iterator> map;

   public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (map.find(key) != map.end()) {
            cout << "[CacheHit]" << "Key " << key << " already exists in cache, moving it to front" << endl;

            moveToFront(key);

            return map[key]->value;
        }

        cout << "[CacheMiss] Update cache from backend data.";
        if (backendValues.find(key) == backendValues.end()) {
            throw runtime_error(format("Key={} not found in backend", key));
        }

        if (isfull()) {
            cout << "[CacheFull] Cache is full, removing last pageframe." << dll.back().to_string() << endl;
            removeFromEnd();
        }

        cout << "[CacheUpdate] Inserting " << key << "," << backendValues[key] << " to cache." << endl;
        insertAtFront(key, backendValues[key]);
    }

    void put(int key, int val) {
        if (map.find(key) != map.end()) {
            // remove current key as it will be updated down.
            dll.erase(map[key]);
            map.erase(key);
        } else if (map.size() == capacity) {
            removeFromEnd();
        }

        dll.push_front(KeyValue(key, val));
        map[key] = dll.begin();
    }

    void remove(int key) {
        if (map.find(key) == map.end()) {
            throw runtime_error(format("Key={} doesn't exist in cache.", key));
        }

        auto iter = map[key];
        dll.erase(iter);
        map.erase(key);
    }

   private:
    void moveToFront(int key) {
        auto v = map[key];
        dll.insert(dll.begin(), *v);
        dll.erase(v);
        map[key] = dll.begin();
    }

    bool isfull() {
        return map.size() == capacity;
    }

    void removeFromEnd() {
        auto v = dll.back();
        dll.pop_back();
        map.erase(v.key);
    }

    void insertAtFront(int key, int val) {
        dll.push_front(KeyValue(key, val));
        map.insert({key, dll.begin()});
    }
};
}  // namespace lrucache1

namespace lrucachev2 {
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> fsec;

template <class K, class V>
class LRUCache {
    using E = pair<K, V>;

   private:
    int capacity;
    list<E> dq;
    unordered_map<K, list<E>::iterator> map;
    ofstream out;
    ifstream in;
    string file;

   public:
    LRUCache(int capacity) : capacity(capacity) {
        this->file = "D:/out.log";
        this->in.open(file);
    }

    static void test() {
        int capacity = 5;
        LRUCache<int, int> lru(capacity);
        lru.put(1, 100);
        lru.put(2, 200);
        lru.put(3, 300);
        lru.put(4, 400);
        lru.put(5, 500);
        lru.put(6, 600);
        cout << "Value for key 1:" << lru.get(1) << endl
             << endl;
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

    void put(K key, V val) {
        cout << "Inserting: " << key << " " << val << endl;
        in.clear();
        auto currentState = readAll();
        if (currentState.find(to_string(key)) != currentState.end()) {
            currentState[to_string(key)] = to_string(val);
        } else {
            currentState.insert({to_string(key), to_string(val)});
        }
        writeAll(currentState);
        in.clear();
    }

    V get(K key) {
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

        dq.push_front({key, val});
        map[key] = dq.begin();
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = std::chrono::duration_cast<ms>(fs);
        cout << "Value loaded from cache data in " << d.count() << "ms." << endl;

        return val;
    }

    bool readFromFile(K key, E &response) {
        string line;
        while (in >> line) {
            pair<string, string> parts = split(line, ':');
            if (stoi(parts.first) == key) {
                cout << "Found data in backend for key " << key << endl;
                response = {stoi(parts.first), stoi(parts.second)};
                return true;
            }
        }

        return false;
    }

    pair<string, string> split(string line, char ch) {
        size_t pos = line.find(ch);
        return {line.substr(0, pos), line.substr(pos + 1)};
    }

    unordered_map<string, string> readAll() {
        unordered_map<string, string> map;
        string line;
        while (in >> line) {
            pair<string, string> parts = split(line, ':');
            map.insert(parts);
        }

        return map;
    }

    void writeAll(unordered_map<string, string> currentState) {
        out.open(file, std::ofstream::out | std::ofstream::trunc);
        for (auto cur : currentState) {
            out << cur.first << ":" << cur.second << endl;
        }
        out.flush();
        out.close();
    }
};
}  // namespace lrucachev2

namespace lrucache3 {
template <class K, class V>
class LRUCache {
    struct Node {
        K key;
        V val;
        struct Node *prev, *next;

        Node(K key, V val, struct Node *prev = nullptr, struct Node *next = nullptr) {
            this->key = key;
            this->val = val;

            this->prev = prev;
            this->next = next;
        }

        string to_string() {
            stringstream ss;
            ss << "{";
            ss << key << ",";
            ss << val;
            ss << "}";

            return ss.str();
        }
    };

    class DLL {
        Node *head = nullptr;
        Node *tail = nullptr;

       public:
        DLL() {}

        ~DLL() {
            while (tail) {
                auto prev = tail;
                tail = tail->next;
                delete prev;
            }
            head = tail = nullptr;
        }

        // implement move, copy constructor and assignment operators as well

        void push_back(K key, V val) {
            push_back(new Node(key, val));
        }

        void push_back(Node *node) {
            if (head == nullptr)
                head = tail = node;
            else {
                tail->next = node;
                node->prev = tail;
                tail = tail->next;
            }
        }

        void push_front(K key, V val) {
            push_front(new Node(key, val));
        }

        void push_front(Node *node) {
            if (head == nullptr)
                head = tail = node;
            else {
                node->next = head;
                head->prev = node;
                head = node;
            }
        }

        void pop_back() {
            if (head == nullptr)
                throw exception("List is empty.");

            else if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                tail = tail->prev;
                delete tail->next;

                tail->next = nullptr;
            }
        }

        void remove(Node *elem) {
            if (!elem) throw exception("Invalid list element to remove.");

            Node *prev = elem->prev ? elem->prev : nullptr;
            Node *next = elem->next ? elem->next : nullptr;

            delete elem;

            if (prev)
                prev->next = next;
            else
                head = next;

            if (next)
                next->prev = prev;
            else
                tail = prev;
        }

        Node *back() {
            return tail;
        }

        Node *front() {
            return head;
        }

        void print() {
            Node *tmp = head;
            while (tmp != tail) {
                cout << tmp->to_string() << " ";
                tmp = tmp->next;
            }
        }
    };

   private:
    DLL list;
    unordered_map<K, Node *> map;
    int size, capacity;

   public:
    LRUCache(int n) : capacity(n) {
        size = 0;
    }

    void put(K key, V val) {
        // if key already exists
        if (map.find(key) != map.end()) {
            cout << format("[CachePut] Key {} already exists in cache. Updating val={}", key, val) << endl;

            list.remove(map[key]);
            map.erase(key);

            size--;
        }

        // if size is already full.
        if (size == capacity) {
            cout << format("[CachePut] Cache full. Removing key {}, val={}", list.back()->key, list.back()->val) << endl;

            map.erase(list.back()->key);
            list.pop_back();

            size--;
        }

        cout << format("[CachePut] Cache Insert key {}, val={}", key, val) << endl;
        auto new_node = new Node(key, val);
        list.push_front(new_node);

        map[key] = new_node;

        size++;
    }

    V get(K key) {
        if (map.find(key) == map.end()) {
            cout << format("[CacheMiss] Key {} not found in cache.", key) << endl;
            throw runtime_error(format("Key {} not found.", key));
        }

        auto list_elem = map[key];
        auto val = list_elem->val;
        list.remove(list_elem);

        auto new_head = new Node(key, val);
        list.push_front(new_head);

        cout << format("[CacheHit] Cache read key {}, val={}", key, val) << endl;

        return val;
    }
};

class LRUCacheTest {
   public:
    static void test() {
        LRUCache<int, int> cache(4);

        auto validate_get = [&cache](auto key, bool error = false, auto expected_val = -1) {
            try {
                auto val = cache.get(key);
                if (error)
                    assert(true);
                else
                    assert(expected_val == val);
            } catch (exception e) {
                cout << e.what() << endl;
                if (!error) assert(true);
            }
        };

        cache.put(1, 2);
        cache.put(1, 3);
        validate_get(2, true, -1);
        validate_get(1, false, 3);
        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(3, 3);
        cache.put(4, 4);
        cache.put(5, 5);
        cache.put(6, 6);
        cache.put(7, 7);
        validate_get(0, true, -1);
        validate_get(1, false, 1);
        validate_get(2, false, 2);
        validate_get(3, true, 3);
        validate_get(4, false, 4);
        validate_get(5, true, 5);
        validate_get(6, false, 6);
        validate_get(7, false, 7);
        validate_get(8, true, -1);
        validate_get(9, true, -1);
    }
};
}  // namespace lrucache3

namespace concurrentlrucache {
template <typename K, typename V>
class DLL {
   public:
    class Node {
       public:
        K key;
        V val;
        Node *prev;
        Node *next;
        Node(K key, V val) : key(key), val(val), prev(nullptr), next(nullptr) {}
        string to_string() {
            return std::string(key) + "," + std::to_string(val);
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;

    void push_back(K key, V val) {
        if (!head)
            head = tail = new Node(key, val);
        else {
            tail->next = new Node(key, val);
            tail->next->prev = tail;
        }
    }

    Node *push_front(K key, V val) {
        if (!head)
            head = tail = new Node(key, val);
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

    void moveToFront(Node *node) {
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
    unordered_map<K, DLL<string, string>::Node *> map;
    DLL<K, V> dll;

   public:
    LRU(int capacity) : capacity(capacity) {}
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
                cout << endl
                     << endl;
            } catch (exception e) {
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
}  // namespace concurrentlrucache

namespace concurrentlrucache2 {
using KEY = string;
using VALUE = string;
using DataSource = unordered_map<KEY, VALUE>;

template <class K, class V>
class Node {
   public:
    K key;
    V val;
    Node *prev, *next;
    Node(K key, V val) : key(key), val(val), prev(nullptr), next(nullptr) {}
};

template <class K, class V>
class LinkedList {
   private:
    Node<K, V> *head = nullptr;
    Node<K, V> *tail = nullptr;

   public:
    void insert(Node<K, V> *node) {
        if (head == nullptr) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    Node<K, V> *evict() {
        if (head == nullptr || tail == nullptr) return head;
        auto rear = tail;
        cout << "Evicting {" << rear->key << ", " << rear->val << "}." << endl;
        tail = tail->prev;
        if (tail == nullptr) head = nullptr;

        return rear;
    }

    void moveToFront(Node<K, V> *node) {
        if (node == nullptr) return;
        cout << "Moving {" << node->key << ", " << node->val << "} to front." << endl;
        Node<K, V> *prev = node->prev;
        Node<K, V> *next = node->next;

        if (prev != nullptr) prev->next = next;
        if (next != nullptr)
            next->prev = prev;
        else
            tail = prev;

        node->next = head;
        head = node;
    }

    Node<K, V> *getRoot() {
        return head;
    }
};

template <class K, class V>
class ConcurrentLRU {
    int sz = 0;
    int capacity = 0;
    unordered_map<K, Node<K, V> *> map;
    LinkedList<K, V> list;
    int inserts = 0, hits = 0, misses = 0, evicts = 0;

   public:
    ConcurrentLRU(int capacity) : capacity(capacity) {}
    void put(K key, V val) {
        if (map.find(key) != map.end()) {
            cout << "Already exist {" << key << ", " << val << "}." << endl;
            return;
        }

        cout << "Put {" << key << ", " << val << "}" << endl;
        Node<K, V> *v = new Node<K, V>(key, val);
        if (sz >= capacity) {
            auto res = list.evict();
            sz--;
            map.erase(res->key);
            delete res;
            evicts++;
        }

        map.insert({key, v});
        list.insert(v);
        inserts++;
        sz++;
    }

    V get(K key) {
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

    tuple<int, int, int, int> metrics() {
        return {hits, misses, inserts, evicts};
    }
};

class ThreadPool {
};

class ConcurrentLRUTester {
   private:
    ConcurrentLRU<KEY, VALUE> *lru = nullptr;

   public:
    ConcurrentLRUTester(int lruSize, DataSource &in, DataSource &out) {
        lru = new ConcurrentLRU<KEY, VALUE>(lruSize);
    }

    void put() {
    }

    void get() {
    }
};

class Test {
   private:
    ConcurrentLRU<string, string> *lru = nullptr;

   public:
    Test() {
        lru = new ConcurrentLRU<string, string>(10);
    }
    void test() {
        insertAndValidate({1, 10}, {0, 0, 10, 0});
        insertAndValidate({6, 15}, {0, 0, 15, 5});
        fetchAndValidate({1, 20}, {6, 15}, {10, 10, 15, 5});
    }

    void insertAndValidate(tuple<int, int> range, tuple<int, int, int, int> expect) {
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

    void fetchAndValidate(tuple<int, int> accessRange, tuple<int, int> presentRange, tuple<int, int, int, int> expect) {
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
}  // namespace concurrentlrucache2