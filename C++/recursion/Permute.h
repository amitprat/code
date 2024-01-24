#pragma once
#include "../Header.h"

class Permute {
public:
    static void test() {
        int n = 4;
        vector<int> arr(2 * n, 0);

        Permute p;
        unordered_set<int> visited;

        if (p.permute(arr, 0, n, visited)) {
            for (auto e : arr) cout << e << " ";
            cout << endl;
        }
    }

    bool permute(vector<int>& arr, int index, int n, unordered_set<int>& visited) {
        if (visited.size() == n) return true;
        if (index == arr.size() || arr[index] != 0) return false;

        for (int i = 1; i <= n; i++) {
            if (visited.find(i) != visited.end()) continue;
            if (arr[index + i + 1] != 0) continue;

            arr[index] = arr[index + i + 1] = i;
            visited.insert(i);

            if (permute(arr, index + 1, n, visited)) return true;

            arr[index] = arr[index + i + 1] = 0;
            visited.erase(i);
        }
        return false;
    }
};