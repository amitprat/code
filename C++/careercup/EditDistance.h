#include "../header.h"

class EditDistance {
   public:
    static void test() {
        string str1 = "sunday";
        string str2 = "saturday";

        EditDistance obj;
        int distance = obj.getEditDistance(str1, str2);
        cout << "Distance : " << distance << endl;
    }

   private:
    int getEditDistance(string &s1, string &s2) {
        int n = s1.length();
        int m = s2.length();

        vector<vector<int>> memo(n, vector<int>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0)  // if both strings are empty
                    memo[i][j] = 0;
                else if (i == 0)  // if first string is empty, we need to insert character to match second string char
                    memo[i][j] = memo[i][j - 1] + insert_cost;
                else if (j == 0)  // if second string is empty, we need to delete character to match second string char
                    memo[i][j] = memo[i - 1][j] + delete_cost;
                else if (s1[i] == s2[j])  // if current char matches in both strings, find the previous minimum of same length str
                    memo[i][j] = memo[i - 1][j - 1];
                else  // minimize the distance taking minimum of replace, delete and insert cost
                {
                    memo[i][j] = memo[i - 1][j - 1] + replace_cost;
                    memo[i][j] = min(memo[i][j], min(memo[i - 1][j] + insert_cost, memo[i][j - 1] + delete_cost));
                }
            }
        }

        return memo[n - 1][m - 1];
    }

   private:
    int insert_cost = 1;
    int delete_cost = 1;
    int replace_cost = 1;
};