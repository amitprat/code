#include "../header.h"

class TaskSchedulingWithCooldown {
   public:
    static void test() {
        TaskSchedulingWithCooldown obj;
        vector<pair<vector<char>, int>> inputs = {
            {{'A', 'B', 'C', 'D'}, 3},
            {{'A', 'B', 'A', 'D'}, 3},
            {{'A', 'A', 'A', 'A'}, 3},
            {{'A', 'B', 'C', 'A', 'C', 'B', 'D', 'A'}, 4},
            {{'A', 'A', 'A', 'B', 'B', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'}, 7}};
        for (auto& input : inputs) {
            auto tasks = input.first;
            int k = input.second;
            int totalSpace = obj.leastInterval(tasks, k);
            cout << format("Input={}, K={}, totalSpace={}", to_string(tasks), k, totalSpace) << endl;
        }
    }

   private:
    int leastInterval(vector<char>& tasks, int K) {
        using P = pair<int, int>;
        auto comparator = [](const auto& f, const auto& s) { return f.second < s.second; };
        priority_queue<P, vector<P>, decltype(comparator)> pq;

        unordered_map<char, int> freqMap;
        for (auto& task : tasks) freqMap[task]++;

        for (auto& e : freqMap) pq.push({e.first, e.second});

        int period = 0;
        while (!pq.empty()) {
            vector<char> curTasks;
            vector<pair<int, int>> rest;

            // add current task to list
            auto cur = pq.top();
            pq.pop();
            curTasks.push_back(cur.first);
            period++;  // increment period for current element

            // reduce occurance of this element and insert into rest
            cur.second--;
            if (cur.second) rest.push_back(cur);

            // calculate cooldown period
            int cooldown = 0;
            if (pq.size() < K) cooldown = K - pq.size();  // cooldown period

            // reduce frequency of rest of element
            int mn = min((int)pq.size(), K);
            period += mn;

            while (mn--) {
                auto top = pq.top();
                pq.pop();
                top.second--;
                curTasks.push_back(top.first);

                if (top.second) rest.push_back(top);
            }

            // insert rest to pq back
            for (auto& e : rest) pq.push(e);

            // add the remaining cooldown period
            if (pq.size()) {
                period += cooldown;
                vector<char> coolDownTasks(cooldown, '_');
                curTasks.insert(curTasks.end(), coolDownTasks.begin(), coolDownTasks.end());
            }

            cout << curTasks << endl;
        }

        return period;
    }

   private:
    int leastInterval2(int N, int K, vector<char>& tasks) {
        // code here
        int freq[26] = {0};
        int maxF = 0;

        for (auto i : tasks) {
            freq[i - 'A']++;
            maxF = max(maxF, freq[i - 'A']);
        }

        int maxFcount = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] == maxF) maxFcount++;
        }

        int time = (maxF - 1) * (K + 1) + maxFcount;

        return max(time, N);
    }
};