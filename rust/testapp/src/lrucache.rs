use std::collections::{HashMap, LinkedList};

struct LRUCache<K, V> {
    capacity: usize,
    cache_map: HashMap<K, (V, usize)>,
    lru_list: LinkedList<V>,
}

impl<K: Eq + std::hash::Hash, V> LRUCache<K, V> {
    fn new(capacity: usize) -> Self {
        LRUCache {
            capacity,
            cache_map: HashMap::new(),
            lru_list: LinkedList::new(),
        }
    }

    fn get(&mut self, key: &K) -> Option<&V> {
        if let Some((value, access_time)) = self.cache_map.get_mut(key) {
            let mut split_list = self.lru_list.split_off(*access_time);
            let val = split_list.pop_front().unwrap();
            self.lru_list.append(&mut split_list);
            self.cache_map.remove(key.clone());

            self.lru_list.push_front(val);
            *access_time = 0;
            Some(value)
        } else {
            None
        }
    }

    fn put(&mut self, key: K, value: V) {
        if self.cache_map.contains_key(&key) {
            let access_time = self.cache_map.get_mut(&key).unwrap().1;
            let mut split_list = self.lru_list.split_off(access_time);
            split_list.pop_front();
            self.lru_list.append(&mut split_list);
        } else if self.cache_map.len() >= self.capacity {
            if let Some(removed_key) = self.lru_list.pop_front() {
                self.cache_map.remove(&removed_key);
            }
        }

        self.lru_list.push_front(key.clone());
        self.cache_map.insert(key, (value, 0));
    }
}

pub fn lru_cache() {
    let mut cache = LRUCache::new(2);
    cache.put(1, "value1");
    cache.put(2, "value2");

    println!("{:?}", cache.get(&1)); // Some("value1")

    cache.put(3, "value3");

    println!("{:?}", cache.get(&2)); // None, because it was the least recently used

    cache.put(4, "value4");

    println!("{:?}", cache.get(&1)); // None, because it was removed due to capacity constraint
}
