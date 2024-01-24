#pragma once
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class FindMinRange {
   public:
    static void test(vector<vector<int>> arrs) {
        FindMinRange fmr;
        vector<int> result = fmr.findMinRangeOptimized(arrs);
        cout << "Min range: [" << result[0] << ", " << result[1] << "]" << endl;
    }

   private:
    vector<int> findMinRange(vector<vector<int>> arrs) {
        vector<int> indices(arrs.size(), 0);
        vector<int> result = {0, INT_MAX};
        int minDiff = INT_MAX;

        if (arrs.size() == 0)
            return result;

        while (true) {
            pair<int, int> mnmxIndex = findMinAndMax(arrs, indices);
            int mnIndex = indices[mnmxIndex.first];
            int mxIndex = indices[mnmxIndex.second];

            if (arrs[mnmxIndex.second][mxIndex] - arrs[mnmxIndex.first][mnIndex] < minDiff) {
                minDiff = arrs[mnmxIndex.second][mxIndex] - arrs[mnmxIndex.first][mnIndex];
                result = {arrs[mnmxIndex.first][mnIndex], arrs[mnmxIndex.second][mxIndex]};
            }

            indices[mnmxIndex.first]++;

            if (indices[mnmxIndex.first] >= arrs[mnmxIndex.first].size())
                break;
        }

        return result;
    }

    pair<int, int> findMinAndMax(vector<vector<int>> arrs, vector<int> indices) {
        pair<int, int> result = {0, 0};

        for (int i = 1; i < indices.size(); i++) {
            if (arrs[i][indices[i]] < arrs[result.first][indices[result.first]])
                result.first = i;
            if (arrs[i][indices[i]] > arrs[result.second][indices[result.second]])
                result.second = i;
        }

        return result;
    }

   private:
    vector<int> findMinRangeOptimized(vector<vector<int>> arrs) {
        // store pair of arr value to {arr index, postition in arr}
        using p = pair<int, pair<int, int>>;
        priority_queue<p, vector<p>, greater<p>> pq;
        vector<int> result = {0, INT_MAX};

        // populate minheap with first element of each array
        int mx = INT_MIN;
        for (int i = 0; i < arrs.size(); i++) {
            pq.push({arrs[i][0], {i, 0}});
            mx = max(mx, arrs[i][0]);
        }

        while (!pq.empty()) {
            auto front = pq.top();
            int mn = front.first;
            int idx = front.second.first;
            int pos = front.second.second;
            pq.pop();

            // if this results into new lowest, update result
            if (mx - mn < result[1] - result[0]) {
                result = {mn, mx};
            }

            // increment the position of smallest element array
            pos++;
            if (pos >= arrs[idx].size())
                break;

            // update max and insert next value from min array
            mx = max(mx, arrs[idx][pos]);
            pq.push({arrs[idx][pos], {idx, pos}});
        }

        return result;
    }
};