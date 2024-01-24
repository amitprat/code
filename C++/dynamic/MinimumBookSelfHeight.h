#pragma once
#include "../Header.h"

class MinBookselfHeight {
public:
    static void test() {
        MinBookselfHeight obj;
        vector<vector<int>> books = {
            {1,1},
            {2,3},
            {2,3},
            {1,1},
            {1,1},
            {1,1},
            {1,2}
        };
        int width = 4;

        cout << "MinHeight using dp = " << obj.getMinHeight(books, width) << endl;

        int minHeight = INT_MAX;
        obj.getMinHeightRec(books, 0, width, 0, minHeight);
        cout << "MinHeight using recrusion = " << minHeight << endl;
    }

    void getMinHeightRec(vector<vector<int>>& books, int index, int width, int curHeight, int& minHeight) {
        if (index == books.size()) {
            minHeight = min(minHeight, curHeight);
            return;
        }

        int w = 0;
        int h = 0;
        for (int i = index; i < books.size(); i++) {
            w += books[i][0];
            h = max(h, books[i][1]);
            if (w > width) break;
            getMinHeightRec(books, i + 1, width, curHeight + h, minHeight);
        }
    }

    int getMinHeight(vector<vector<int>>& books, int width) {
        int n = books.size();
        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= books.size(); i++) {
            int w = books[i - 1][0];
            int h = books[i - 1][1];
            dp[i] = dp[i - 1] + h;

            for (int j = i - 1; j >= 1 && w + books[j - 1][0] <= width; j--) {
                h = max(h, books[j - 1][1]);
                w += books[j - 1][0];
                dp[i] = min(dp[i], h + dp[j - 1]);
            }
        }
        return dp[n];
    }
};