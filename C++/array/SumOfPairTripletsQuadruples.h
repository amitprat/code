#pragma once
#include "../header.h"
using namespace std;

class SumOfPairTripletsQuadruples {
   public:
    static void test(vector<int> arr, int k) {
        SumOfPairTripletsQuadruples obj;

        {
            cout << "Pair Sum:: ";
            auto res1 = obj.pairSumUsingMap(arr, k);
            auto res2 = obj.pairSumUsingSort(arr, k);

            assert(res1 == res2);

            cout << "Output: ";
            cout << res1.first << " " << res1.second << endl;
        }

        {
            cout << "Triplet Sum:: ";
            auto res1 = obj.tripletSumUsingMap(arr, k);
            auto res2 = obj.tripletSumUsingSort(arr, k);

            assert(res1 == res2);

            cout << "Output: ";
            cout << get<0>(res2) << " " << get<1>(res2) << " " << get<2>(res2) << endl;
        }

        {
            cout << "Quadruple Sum:: ";

            auto res1 = obj.quadrupleSum(arr, k);
            cout << "Output: ";
            cout << get<0>(res1) << " " << get<1>(res1) << " " << get<2>(res1) << " " << get<3>(res1) << endl;

            cout << "All four sum: ";
            auto res2 = obj.fourSum2(arr, k);
            for (auto& res : res2) {
                cout << res << ", ";
            }
        }
    }

   private:
    pair<int, int> pairSumUsingSort(vector<int> v, int sum) {
        sort(v.begin(), v.end());

        int i = 0, j = v.size() - 1;
        while (i < j) {
            if (v[i] + v[j] == sum)
                return {v[i], v[j]};
            else if (v[i] + v[j] < sum)
                i++;
            else
                j--;
        }

        return {-1, -1};
    }

    pair<int, int> pairSumUsingMap(vector<int> v, int sum) {
        unordered_map<int, int> m;
        for (int i = 0; i < v.size(); i++) {
            int remSum = sum - v[i];
            if (m.find(remSum) == m.end()) {
                m[v[i]] = i;
            } else {
                auto j = m[remSum];
                if (i != j) {
                    return {v[i], v[j]};
                }
            }
        }
    }

   private:
    tuple<int, int, int> tripletSumUsingSort(vector<int> v, int sum) {
        sort(v.begin(), v.end());

        for (int i = 0; i < v.size() - 1; i++) {
            int j = i + 1;
            int k = v.size() - 1;

            while (j < k) {
                if (v[i] + v[j] + v[k] == sum)
                    return {v[i], v[j], v[k]};
                else if (v[i] + v[j] + v[k] < sum)
                    j++;
                else
                    k--;
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
    }

   private:
    // find four sum
    tuple<int, int, int, int> quadrupleSum(vector<int> arr, int target) {
        unordered_map<int, pair<int, int>> pairSumMap;
        for (int i = 0; i < arr.size() - 1; i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int curSum = arr[i] + arr[j];  // current sum
                int remSum = target - curSum;
                if (pairSumMap.find(remSum) == pairSumMap.end()) {
                    pairSumMap[curSum] = {i, j};
                } else {
                    auto candPair = pairSumMap[curSum];  // candidate pair
                    auto [l, m] = candPair;
                    if (l != i && l != j && m != i && m != j) {
                        return {arr[i], arr[j], arr[l], arr[m]};
                    }
                }
            }
        }

        return {-1, -1, -1, -1};
    }

    // find all quadruples which makes to target sum
    vector<vector<int>> fourSum2(const vector<int>& arr, int target) {
        vector<vector<int>> result;
        int n = arr.size();
        if (n < 4) return result;

        using P = pair<int, int>;
        unordered_map<int, P> map;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int curSum = arr[i][j];
                if (map.find(curSum) != map.end()) {
                    auto [l, m] = map[curSum];  // existing value
                    if (i != l && i != m && j != l && j != m) {
                        result.push_back({i, j, l, m});
                    }
                } else {
                    map[curSum] = {i, j};
                }
            }
        }

        return result;
    }
};