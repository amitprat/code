#pragma once
#include "../header.h"
using namespace std;

class SumOfPairTripletsQuadruples {
   public:
    static void test() {
        SumOfPairTripletsQuadruples obj;
        vector<int> arr = {-8, -4, -2, -1, 1, 3, 5, 8, 12};
        int k = 0;

        cout << "Pair Sum:: ";
        auto res1 = obj.pairSumUsingMap(arr, k);
        auto res2 = obj.pairSumUsingSort(arr, k);
        cout << "Output: " << res1.first << " " << res1.second << endl;
        assert(res1 == res2);

        cout << "Triplet Sum:: ";
        auto t1 = obj.tripletSumUsingMap(arr, k);
        auto t2 = obj.tripletSumUsingSort(arr, k);
        cout << "Output: " << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;
        assert(t1 == t2);

        cout << "Quadruple Sum:: ";
        auto q1 = obj.quadrupleSum(arr, k);
        cout << "Output: " << get<0>(q1) << " " << get<1>(q1) << " " << get<2>(q1) << " " << get<3>(q1) << endl;

        cout << "All four sum: ";
        auto allFour = obj.fourSum2(arr, k);
        for (const auto &v : allFour)
            for (int val : v) cout << val << ' ';
        cout << endl;
    }

   private:
    pair<int, int> pairSumUsingSort(vector<int> v, int sum) {
        sort(v.begin(), v.end());
        int i = 0, j = v.size() - 1;
        while (i < j) {
            int s = v[i] + v[j];
            if (s == sum) return {v[i], v[j]};
            (s < sum) ? ++i : --j;
        }
        return {-1, -1};
    }

    pair<int, int> pairSumUsingMap(vector<int> v, int sum) {
        unordered_map<int, int> m;
        for (int i = 0; i < v.size(); ++i) {
            int rem = sum - v[i];
            if (m.contains(rem)) return {v[i], rem};
            m[v[i]] = i;
        }
        return {-1, -1};
    }

   private:
    tuple<int, int, int> tripletSumUsingSort(vector<int> v, int sum) {
        sort(v.begin(), v.end());
        for (int i = 0; i < (int)v.size() - 2; ++i) {
            int j = i + 1, k = v.size() - 1;
            while (j < k) {
                int s = v[i] + v[j] + v[k];
                if (s == sum) return {v[i], v[j], v[k]};
                (s < sum) ? ++j : --k;
            }
        }
        return {-1, -1, -1};
    }

    tuple<int, int, int> tripletSumUsingMap(vector<int> v, int sum) {
        unordered_map<int, int> m;

        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int curSum = v[i] + v[j];
                int remSum = sum - curSum;
                if (m.find(remSum) == m.end()) {
                    m[v[i]] = i;
                    m[v[j]] = j;
                } else {
                    auto k = m[remSum];
                    if (i != k && j != k) {
                        return {v[i], v[j], v[k]};
                    }
                }
            }
        }

        return {-1, -1, -1};
    }

   private:
    // find four sum
    tuple<int, int, int, int> quadrupleSum(vector<int> v, int sum) {
        unordered_map<int, pair<int, int>> seen;
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = i + 1; j < (int)v.size(); ++j) {
                int curSum = v[i] + v[j];
                int rem = sum - curSum;
                if (seen.contains(rem)) {
                    auto [x, y] = seen[rem];
                    if (x != i && x != j && y != i && y != j)
                        return {v[x], v[y], v[i], v[j]};
                } else {
                    seen[curSum] = {i, j};
                }
            }
        }
        return {-1, -1, -1, -1};
    }

    // find all quadruples which makes to target sum
    vector<vector<int>> fourSum2(const vector<int> &arr, int target) {
        vector<vector<int>> result;
        int n = arr.size();
        if (n < 4)
            return result;

        using P = pair<int, int>;
        unordered_map<int, P> map;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int curSum = arr[i] + arr[j];
                if (map.find(target - curSum) != map.end()) {
                    auto [l, m] = map[target - curSum];  // existing value
                    if (i != l && i != m && j != l && j != m) {
                        result.push_back({arr[i], arr[j], arr[l], arr[m]});
                    }
                } else {
                    map[curSum] = {i, j};
                }
            }
        }

        return result;
    }
};