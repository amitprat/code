#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class ConsistentHashRing {
   public:
    explicit ConsistentHashRing(int virtual_nodes = 100)
        : vnodes_(virtual_nodes) {}

    void add_node(const std::string& node_id) {
        for (int i = 0; i < vnodes_; ++i) {
            ring_[hash(node_id + "#" + std::to_string(i))] = node_id;
        }
    }

    void remove_node(const std::string& node_id) {
        for (int i = 0; i < vnodes_; ++i) {
            ring_.erase(hash(node_id + "#" + std::to_string(i)));
        }
    }

    std::string get_node(const std::string& key) const {
        if (ring_.empty()) return "NONE";

        uint32_t h = hash(key);
        auto it = ring_.lower_bound(h);
        if (it == ring_.end()) it = ring_.begin();
        return it->second;
    }

   private:
    uint32_t hash(const std::string& s) const {
        return static_cast<uint32_t>(std::hash<std::string>{}(s));
    }

    int vnodes_;
    std::map<uint32_t, std::string> ring_;
};

// ---------- Helper Utilities ----------

using Assignment = std::unordered_map<std::string, std::string>;

Assignment assign_keys(
    const ConsistentHashRing& ring,
    const std::vector<std::string>& keys) {
    Assignment result;
    for (const auto& k : keys) {
        result[k] = ring.get_node(k);
    }
    return result;
}

void print_assignments(const std::string& title, const Assignment& a) {
    std::cout << "\n=== " << title << " ===\n";
    for (const auto& [key, node] : a) {
        std::cout << std::setw(10) << key << " -> " << node << "\n";
    }
}

void print_node_distribution(const Assignment& a) {
    std::unordered_map<std::string, std::vector<std::string>> dist;
    for (const auto& [key, node] : a) {
        dist[node].push_back(key);
    }

    std::cout << "\n--- Per Node Distribution ---\n";
    for (const auto& [node, keys] : dist) {
        std::cout << node << ": ";
        for (const auto& k : keys) std::cout << k << " ";
        std::cout << "\n";
    }
}

void print_diff(const Assignment& before, const Assignment& after) {
    std::cout << "\n--- Key Re-distribution (Diff) ---\n";
    for (const auto& [key, old_node] : before) {
        const auto& new_node = after.at(key);
        if (old_node != new_node) {
            std::cout << key << ": " << old_node << " -> " << new_node << "\n";
        }
    }
}

// ---------- Demo ----------

int main() {
    ConsistentHashRing ring(50);

    std::vector<std::string> nodes = {
        "Node-A", "Node-B", "Node-C"};

    std::vector<std::string> keys = {
        "User1", "User2", "User3", "User4",
        "Tweet1", "Tweet2", "Tweet3", "Tweet4",
        "Session1", "Session2"};

    // Initial cluster
    for (const auto& n : nodes) ring.add_node(n);

    auto initial = assign_keys(ring, keys);
    print_assignments("Initial Assignment", initial);
    print_node_distribution(initial);

    // Remove Node-B
    ring.remove_node("Node-B");
    auto after_remove = assign_keys(ring, keys);

    print_assignments("After Removing Node-B", after_remove);
    print_diff(initial, after_remove);
    print_node_distribution(after_remove);

    // Add Node-D
    ring.add_node("Node-D");
    auto after_add = assign_keys(ring, keys);

    print_assignments("After Adding Node-D", after_add);
    print_diff(after_remove, after_add);
    print_node_distribution(after_add);

    return 0;
}
