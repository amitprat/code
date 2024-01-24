#include "../header.h"

/*
https://www.careercup.com/question?id=5652354158297088

You're given an array of integers(eg [3,4,7,1,2,9,8]) Find the index of values that satisfy A+B = C+D, where A,B,C & D are integers values in the array.

Eg: Given [3,4,7,1,2,9,8] array
The following
3+7 = 1+9 satisfies A+B=C+D
so print (0,2,3,5)

I use hash map to record the sum of two pair and find two pairs which has the same sum. Time is O(n^2)

struct Node {
    int x;
    int y;
    Node(int a = 0, int b = 0) : x(a), y(b){};
};
vector<int> Print4Sum(vector<int> A) {
    int tsum, l = A.size();
    vector<int> ans;
    if (l < 4) return ans;

    map<int, Node> hashmap;
    for (int i = 0; i < l - 1; ++i)
        for (int j = i + 1; j < l; ++j) {
            tsum = A[i] + A[j];
            if (hashmap.find(tsum) == hashmap.end()) {
                Node tnode = Node(i, j);
                hashmap[tsum] = tnode;
            } else {
                Node tnode = hashmap[tsum];
                int x = tnode.x, y = tnode.y;
                if (x != i && x != j && y != i && y != j) {
                    ans.push_back(i);
                    ans.push_back(j);
                    ans.push_back(x);
                    ans.push_back(y);
                    sort(ans.begin(), ans.end());
                    return ans;
                }
            }
        }
    return ans;
}
*/

class FindFourSum {
   public:
    static void test() {
        {
            vector<int> arr = {3, 4, 7, 1, 2, 9, 8};

            // fourSum(arr);
            // fourSum2(arr);
            auto v = fourSum3(arr);
            cout << to_string(v.first) << ", " << to_string(v.second) << endl;
        }
        cout << endl;

        {
            vector<int> arr = {3, 7, 1, 2, 3, 1, 2};

            auto v = fourSum3(arr);
            cout << to_string(v.first) << ", " << to_string(v.second) << endl;
        }
    }

    static vector<int> fourSum(vector<int> arr) {
        unordered_map<int, vector<pair<int, int>>> sumPair;
        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                sumPair[s].push_back({i, j});
            }
        }

        for (auto e : sumPair) {
            if (e.second.size() > 1) {
                cout << "Pairs with sum " << e.first << " = ";
                for (auto p : e.second) {
                    cout << "{" << arr[p.first] << "," << arr[p.second] << "}, ";
                }
                cout << endl;
            }
        }

        return {};
    }

    static vector<int> fourSum2(vector<int> arr) {
        unordered_map<int, pair<int, int>> pairSumMap;

        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                if (pairSumMap.find(s) == pairSumMap.end()) {
                    pairSumMap[s] = {i, j};
                } else {
                    auto old = pairSumMap[s];
                    if (old.first != i && old.second != j && old.first != i && old.second != j) {
                        return {arr[old.first], arr[old.second], arr[i], arr[j]};
                    }
                }
            }
        }

        return {};
    }

    static pair<pair<int, int>, pair<int, int>> fourSum3(vector<int> arr) {
        unordered_map<int, pair<int, int>> pairSumMap;

        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                if (pairSumMap.find(s) == pairSumMap.end()) {
                    pairSumMap[s] = {i, j};
                } else {
                    auto old = pairSumMap[s];
                    if (old.first != i && old.first != j && old.second != i && old.second != j) {
                        return {{arr[old.first], arr[old.second]}, {arr[i], arr[j]}};
                    }
                }
            }
        }

        return {};
    }
};