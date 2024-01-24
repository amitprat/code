#include "../header.h"

/*
https://careercup.com/question?id=5088794078347264

On a given array with N numbers, find subset of size M (exactly M elements) that equal to SUM.

*/
class FindSubsetOfSizeMEqualsSum {
    void findSubset(vector<int>& vals, int M, int sum) {
        vector<vector<int>> table(sum + 1, vector<int>(M + 1));

        for (int s = 0; s <= sum; s++) {
            for (int i = 0; i <= M; i++) {
                if (s == 0 || i == 0)
                    table[s][i] = 0;
                else if (vals[i - 1] > s)
                    table[s][i] = table[s][i - 1];
                else
                    table[s][i] = max(table[s][i - 1] + 1 + table[s - vals[i - 1]][i - 1]);
            }
        }

        int res = table[sum][M];
        for (int i = M; i > 0 && res > 0; i--) {
            if (res == table[sum][i - 1])
                continue;  // ignore this element
            else {
                cout << vals[i - 1] << " ";
                res -= 1;
                sum -= vals[i - 1];
            }
        }
    }
};