#include <string>
#include <unordered_map>
#include <vector>
#include < iostream>
using namespace std;

static constexpr int MAX_LEVEL = 32;
static constexpr double P = 0.25;

struct ZNode {
    string member;
    double score;
    vector<ZNode*> forward;
    vector<int> span;

    ZNode(string m, double s, int level)
        : member(m), score(s), forward(level, nullptr), span(level, 0) {}
};

class ZSkipList {
    ZNode* head;
    int level;
    int length;

    int randomLevel() {
        int lvl = 1;
        while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    static bool lessThan(double s1, const string& m1,
                         double s2, const string& m2) {
        return s1 < s2 || (s1 == s2 && m1 < m2);
    }

   public:
    ZSkipList() {
        level = 1;
        length = 0;
        head = new ZNode("", 0, MAX_LEVEL);
    }

    void insert(double score, const string& member) {
        ZNode* update[MAX_LEVEL];
        int rank[MAX_LEVEL] = {0};

        ZNode* x = head;
        for (int i = level - 1; i >= 0; i--) {
            rank[i] = (i == level - 1) ? 0 : rank[i + 1];
            while (x->forward[i] && lessThan(x->forward[i]->score, x->forward[i]->member, score, member)) {
                rank[i] += x->span[i];
                x = x->forward[i];
            }
            update[i] = x;
        }

        int lvl = randomLevel();
        if (lvl > level) {
            for (int i = level; i < lvl; i++) {
                update[i] = head;
                update[i]->span[i] = length;
            }
            level = lvl;
        }

        ZNode* node = new ZNode(member, score, lvl);
        for (int i = 0; i < lvl; i++) {
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;

            node->span[i] = update[i]->span[i] - (rank[0] - rank[i]);
            update[i]->span[i] = (rank[0] - rank[i]) + 1;
        }

        for (int i = lvl; i < level; i++)
            update[i]->span[i]++;

        length++;
    }

    int rank(double score, const string& member) {
        ZNode* x = head;
        int rank = 0;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] &&
                   lessThan(x->forward[i]->score, x->forward[i]->member,
                            score, member)) {
                rank += x->span[i];
                x = x->forward[i];
            }
        }
        return rank;
    }

    void range(int start, int count) {
        ZNode* x = head;
        int traversed = 0;

        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] && traversed + x->span[i] <= start) {
                traversed += x->span[i];
                x = x->forward[i];
            }
        }

        x = x->forward[0];
        while (count-- && x) {
            cout << x->member << " (" << x->score << ")\n";
            x = x->forward[0];
        }
    }
};

class RedisZSet {
    unordered_map<string, double> dict;
    ZSkipList zsl;

   public:
    void zadd(const string& member, double score) {
        if (dict.count(member)) {
            // Remove not implemented (simplified)
        }
        dict[member] = score;
        zsl.insert(score, member);
    }

    double zscore(const string& member) {
        return dict.at(member);
    }

    int zrank(const string& member) {
        return zsl.rank(dict.at(member), member);
    }

    void zrange(int start, int count) {
        zsl.range(start, count);
    }
};

int main() {
    srand(time(nullptr));
    RedisZSet zset;

    zset.zadd("alice", 100);
    zset.zadd("bob", 150);
    zset.zadd("carol", 120);

    cout << "Top 2:\n";
    zset.zrange(0, 2);

    cout << "Rank of bob: " << zset.zrank("bob") << "\n";
}
