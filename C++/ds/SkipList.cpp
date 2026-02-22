#include <vector>
using namespace std;

static constexpr int MAX_LEVEL = 32;
static constexpr double P = 0.25;

struct SkipNode {
    int key;
    vector<SkipNode*> forward;
    vector<int> span;

    SkipNode(int k, int level)
        : key(k), forward(level, nullptr), span(level, 0) {}
};

class SkipList {
    SkipNode* head;
    int level;
    int length;

    int randomLevel() {
        int lvl = 1;
        while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

   public:
    SkipList() {
        level = 1;
        length = 0;
        head = new SkipNode(INT_MIN, MAX_LEVEL);
    }

    void insert(int key) {
        SkipNode* update[MAX_LEVEL];
        int rank[MAX_LEVEL] = {0};

        SkipNode* x = head;
        for (int i = level - 1; i >= 0; i--) {
            rank[i] = (i == level - 1) ? 0 : rank[i + 1];
            while (x->forward[i] && x->forward[i]->key < key) {
                rank[i] += x->span[i];
                x = x->forward[i];
            }
            update[i] = x;
        }

        int lvl = randomLevel();
        if (lvl > level) {
            for (int i = level; i < lvl; i++) {
                rank[i] = 0;
                update[i] = head;
                update[i]->span[i] = length;
            }
            level = lvl;
        }

        SkipNode* node = new SkipNode(key, lvl);
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

    int rankOf(int key) {
        SkipNode* x = head;
        int rank = 0;
        for (int i = level - 1; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key) {
                rank += x->span[i];
                x = x->forward[i];
            }
        }
        return rank + 1;  // 1-based rank
    }

    void print() {
        SkipNode* x = head->forward[0];
        while (x) {
            cout << x->key << " ";
            x = x->forward[0];
        }
        cout << "\n";
    }
};

int main() {
    srand(time(nullptr));
    SkipList sl;
    sl.insert(50);
    sl.insert(20);
    sl.insert(40);
    sl.insert(10);

    sl.print();
    cout << "Rank of 40: " << sl.rankOf(40) << "\n";
}
