#pragma once
#include "../Header.h"

class LRUCache {
	struct KeyValue {
		int key, value;
		KeyValue(int key, int value) :key(key), value(value) {}
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

		cout << "[CacheMiss]";
		if (backendValues.find(key) == backendValues.end()) {
			throw runtime_error(format("Key={} not found backend", key));
		}

		if (isfull()) {
			removeFromEnd();
		}

		insertAtFront(key, backendValues[key]);
	}

	void put(int key, int val) {
		if (map.find(key) != map.end()) {
			throw runtime_error(format("Key={} already exists in cache", key));
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

public:
	static void test() {
		LRUCache cache(10);
		vector<int> keys = { 5, 0, 1, 3, 2, 4, 1, 0, 5 };
		srand(time(nullptr));

		for (auto key : keys) {
			try {
				auto v = cache.get(key);
				cout << "Fetched " << key << " = " << v << endl;
			}
			catch (exception e) {
				cout << e.what() << endl;
				cache.put(key, rand());
			}
		}
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
		auto v = dll.back(); dll.pop_back();
		cout << "Cache is full, removing last pageframe " << v.to_string() << endl;
		map.erase(v.key);
	}

	void insertAtFront(int key, int val) {
		dll.push_front(KeyValue(key, val));
		cout << "Inserting " << key << "," << val << " to front." << endl;

		map.insert({ key, dll.begin() });
	}
};