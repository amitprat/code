#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/* ================= Vector Clock ================= */

struct VectorClock {
    unordered_map<string, int> v;

    void tick(const string& node) {
        v[node]++;
    }

    void merge(const VectorClock& other) {
        for (auto& [n, c] : other.v)
            v[n] = max(v[n], c);
    }

    string str() const {
        string s = "{";
        for (auto& [n, c] : v) s += n + ":" + to_string(c) + " ";
        return s + "}";
    }
};

/* ================= Versioned Value ================= */

struct Value {
    string data;
    VectorClock vc;
};

/* ================= Node ================= */

struct Node {
    string id;

    bool alive = true;
    bool permanent_dead = false;

    int heartbeat = 0;
    int missed_heartbeats = 0;

    unordered_map<string, Value> store;
    unordered_map<string, Value> hints;  // hinted handoff buffer

    explicit Node(string id) : id(id) {}
};

/* ================= Cluster ================= */

struct Cluster {
    vector<Node*> all_nodes;
    vector<Node*> replicas;  // current primary replicas
    Node* fallback;          // sloppy quorum node

    int N = 3, W = 2, R = 2;
    int HEARTBEAT_TIMEOUT = 3;
    int time = 0;

    /* ---------- Gossip / Heartbeat ---------- */
    void tick() {
        time++;
        cout << "\n[TICK " << time << "]\n";

        for (auto* n : all_nodes) {
            if (!n->alive) {
                n->missed_heartbeats++;
                if (!n->permanent_dead &&
                    n->missed_heartbeats >= HEARTBEAT_TIMEOUT) {
                    n->permanent_dead = true;
                    cout << "  [PERMANENT FAILURE DETECTED] "
                         << n->id << "\n";
                }
            } else {
                n->heartbeat++;
                n->missed_heartbeats = 0;
            }
        }

        gossip();
    }

    void gossip() {
        cout << "  [GOSSIP STATUS]\n";
        for (auto* n : all_nodes) {
            cout << "   " << n->id
                 << " alive=" << n->alive
                 << " permanent_dead=" << n->permanent_dead
                 << "\n";
        }
    }

    /* ---------- Write ---------- */
    void write(const string& key, const string& value) {
        cout << "\n[WRITE] key=" << key << " value=" << value << "\n";

        int acks = 0;
        for (auto* n : replicas) {
            if (n->alive && !n->permanent_dead) {
                n->store[key].data = value;
                n->store[key].vc.tick(n->id);
                cout << "  wrote to " << n->id << "\n";
                acks++;
            } else {
                // sloppy quorum
                fallback->hints[key] = {value, {}};
                cout << "  hinted write stored on "
                     << fallback->id
                     << " for " << n->id << "\n";
                acks++;
            }

            if (acks >= W) break;
        }

        cout << "  quorum satisfied\n";
    }

    /* ---------- Read ---------- */
    void read(const string& key) {
        cout << "\n[READ] key=" << key << "\n";

        vector<Value> results;
        for (auto* n : replicas) {
            if (n->alive && n->store.count(key)) {
                results.push_back(n->store[key]);
                cout << "  read from " << n->id
                     << " " << n->store[key].vc.str() << "\n";
            }
            if (results.size() >= R) break;
        }

        if (results.empty()) {
            cout << "  NOT FOUND\n";
            return;
        }

        cout << "  returned value=" << results.back().data << "\n";
    }

    /* ---------- Failure / Recovery ---------- */
    void fail(const string& id) {
        auto* n = get(id);
        n->alive = false;
        cout << "\n[FAIL] " << id << " is DOWN\n";
    }

    void recover(const string& id) {
        auto* n = get(id);
        n->alive = true;
        n->missed_heartbeats = 0;
        cout << "\n[RECOVER] " << id << " is BACK\n";

        // hinted handoff
        for (auto it = fallback->hints.begin();
             it != fallback->hints.end();) {
            n->store[it->first] = it->second;
            cout << "  hinted handoff "
                 << it->first << " -> " << id << "\n";
            it = fallback->hints.erase(it);
        }
    }

    /* ---------- Replica Promotion ---------- */
    void promote_fallback() {
        cout << "\n[PROMOTION] Promoting "
             << fallback->id << " as replica\n";

        // remove dead replicas
        replicas.erase(
            remove_if(replicas.begin(), replicas.end(),
                      [](Node* n) { return n->permanent_dead; }),
            replicas.end());

        replicas.push_back(fallback);

        anti_entropy();
    }

    /* ---------- Anti-Entropy (Merkle-like) ---------- */
    void anti_entropy() {
        cout << "\n[ANTI-ENTROPY]\n";
        for (auto* src : replicas) {
            for (auto& [k, v] : src->store) {
                for (auto* dst : replicas) {
                    if (!dst->store.count(k)) {
                        dst->store[k] = v;
                        cout << "  synced " << k
                             << " to " << dst->id << "\n";
                    }
                }
            }
        }
    }

    /* ---------- Helpers ---------- */
    Node* get(const string& id) {
        for (auto* n : all_nodes)
            if (n->id == id) return n;
        assert(false);
    }
};

/* ================= Demo ================= */

int main() {
    Node S1("S1"), S2("S2"), S3("S3"), S4("S4");

    Cluster c;
    c.all_nodes = {&S1, &S2, &S3, &S4};
    c.replicas = {&S1, &S2, &S3};  // correct initial replicas
    c.fallback = &S4;

    c.tick();

    c.write("user:1", "A");
    c.read("user:1");

    c.fail("S2");
    c.tick();

    c.write("user:1", "B");
    c.read("user:1");

    c.tick();
    c.recover("S2");
    c.read("user:1");

    c.fail("S2");
    c.tick();
    c.tick();
    c.tick();  // permanent failure detected

    c.promote_fallback();
    c.read("user:1");

    cout << "\n=== DEMO COMPLETE ===\n";
}
