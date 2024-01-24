#include "../header.h"

class CountAndSay {
   public:
    static void test() {
        CountAndSay obj;
        obj.printCountAndSayRecur(10);
    }

   private:
    void countAndSay(int n) {
        vector<string> dp(n + 1);
        dp[1] = "1";

        for (int i = 2; i < n + 1; i++) {
            string prev = dp[i - 1];
            string cur;
            for (int j = 0; j < prev.length(); j++) {
                int cnt = 1;
                while (j + 1 < prev.length() && prev[j] == prev[j + 1]) {
                    j++;
                    cnt++;
                }

                cur += to_string(cnt) + prev[j];
            }
            dp[i] = cur;
        }

        for (int i = 0; i <= n; i++) {
            cout << dp[i] << endl;
        }
    }

   private:
    void countAndSay2(int n) {
        for (int i = 0; i <= n; i++) {
            cout << countAndSay2Internal(i) << endl;
        }
    }
    string countAndSay2Internal(int n) {
        if (n == 0) return "";
        if (n == 1) return "1";

        string prev = "1";
        for (int i = 2; i < n + 1; i++) {
            string cur;
            for (int j = 0; j < prev.length(); j++) {
                int cnt = 1;
                while (j + 1 < prev.length() && prev[j] == prev[j + 1]) {
                    j++;
                    cnt++;
                }

                cur += to_string(cnt) + prev[j];
            }
            prev = cur;
        }

        return prev;
    }

   private:
    void printCountAndSayRecur(int n) {
        for (int i = 0; i <= 10; i++) cout << countAndSayRecur(i) << endl;
    }
    string countAndSayRecur(int n) {
        if (n == 0) return "";
        if (n == 1) return "1";

        string prev = countAndSayRecur(n - 1);
        string cur;
        for (int i = 0; i < prev.length(); i++) {
            int cnt = 1;
            while (i + 1 < prev.length() && prev[i] == prev[i + 1]) {
                i++;
                cnt++;
            }

            cur += to_string(cnt) + prev[i];
        }

        return cur;
    }
};