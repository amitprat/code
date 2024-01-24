#pragma once
#include "../Header.h"

class ArrangeNumbersByTheirValue {
public:
    static void test() {
        for (int i = 1; i <= 10; i++) {
            vector<int> result;
            bool res = canBePlaced(i, result);
            if (res) {
                cout << i << " : " << to_string(result) << endl;
            }
            else {
                cout << i << " : " << "can't be placed" << endl;
            }
        }
    }

    static bool canBePlaced(int num, vector<int>& result) {
        auto start = chrono::high_resolution_clock::now();
        result.resize(num * 2, 0);
        unordered_set<int> set;
        auto res = canBePlaced(1, num, result);
        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<std::chrono::seconds>(end - start);
        cout << "Time taken to calculate arrangement for " << num << " = " << duration.count() << endl;

        return res;
    }

    static bool canBePlaced(int startNum, int endNum, int pos, vector<int>& result, unordered_set<int>& set) {
        if (set.size() == endNum) return true;
        if (pos >= result.size()) return false;
        if (result[pos] != 0) return canBePlaced(startNum, endNum, pos + 1, result, set);

        for (int i = startNum; i <= endNum; i++) {
            if (set.find(i) != set.end() || pos + i + 1 >= result.size()) continue;
            if (result[pos + i + 1] != 0) continue;

            result[pos] = result[pos + i + 1] = i;
            set.insert(i);
            if (canBePlaced(startNum, endNum, pos + 1, result, set)) return true;
            result[pos] = result[pos + i + 1] = 0;
            set.erase(i);
        }

        return false;
    }

    static bool canBePlaced(int num, int end, vector<int>& result) {
        if (num > end) return true;
        for (int i = 0; i < result.size() - num - 1; i++) {
            if (result[i] == 0 && result[num + i + 1] == 0) {
                result[i] = result[num + i + 1] = num;
                if (canBePlaced(num + 1, end, result)) return true;
                result[i] = result[num + i + 1] = 0;
            }
        }
        return false;
    }
};