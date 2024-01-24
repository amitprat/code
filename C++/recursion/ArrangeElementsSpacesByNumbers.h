#pragma once
#include "../Header.h"

class ArrangeElementsSpacesByNumbers {
public:
    static void test() {
        ArrangeElementsSpacesByNumbers obj;

        for (int num = 1; num <= 10; num++)
        {
            cout << "Arrange elements for " << num << ": ";
            vector<int> arr(2 * num, 0);
            unordered_set<int> visited;

            if (obj.canBeArranged(arr, 0, num, visited)) {
                cout << to_string(arr) << endl;
            }
            else {
                cout << endl;
            }
        }
    }

    bool canBeArranged(vector<int>& arr, int index, int n, unordered_set<int>& visited) {
        if (visited.size() == n) return true;
        if (index >= 2 * n || arr[index] != 0) return false;

        for (int num = 1; num <= n; num++) {
            if (visited.find(num) != visited.end()) continue;

            int nextIndex = index + num + 1;
            if (nextIndex >= 2 * n || arr[nextIndex] != 0) continue;

            arr[index] = arr[nextIndex] = num;
            visited.insert(num);

            if (canBeArranged(arr, index + 1, n, visited)) return true;

            arr[index] = arr[nextIndex] = 0;
            visited.erase(num);
        }

        return false;
    }
};