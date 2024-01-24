#pragma once
#include "../header.h"

template <class K, class V>
class LRUCache2 {
private:
    StorageManager store;
    DoubleLinkedList<Node<K, V>> dll;
    unordered_map<K, Node<K, V>*> map;

public:
    void put(K key, V val) {
        upsert(key, val);
        store.sync();
    }

    V get(K key) {
        pair<K, V> res;
        if (contains(key)) return get_cache(key);

        if (!store.contains(key, res)) throw exception("Key not found!");
        upsert(res.first, res.second);
        return res.second;
    }

    bool remove(K key) {
        if (contains(key)) {
            remove_cache(key);
            store.sync();
            return true;
        }
        else {
            return store.remove(key);
        }
    }

private:
    bool contains(K key) {
        return map.find(key) == map.end();
    }
    void upsert(K key, V val) {
        map[key] = val;
    }
    V get_cache(K key) {
        auto* node = map[key];
        dll.moveToFront(node);
        retur node->val;
    }
    void remove_cache(K key) {
        auto* node = map[key];
        map.erase(key);
        dll.remove(node);
    }
};

class LRUCache2Test {
public:
    static void test() {
        LRUCache2<string, string> obj(fileName, cacheSize);
        obj.put("str1", "val1");
        obj.put("str2", "val2");
        obj.put("str3", "val3");
        obj.get("str1");
        obj.remove("str2");
        obj.get("str2");
    }
};