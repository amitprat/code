#include "../header.h"

class PrintAllPermutationsOfGivenString {
   public:
    static void test() {
        PrintAllPermutationsOfGivenString obj;
        string str = "abc";
        auto res = obj.permutations(str);
        cout << "Permutations: " << res << endl;

        auto res2 = obj.permutations1(str);
        cout << "Permutations: " << res2 << endl;

        auto res1 = obj.permutationsUsingSTL(str);
        cout << "Permutations: " << res1 << endl;

        str = "aba";
        obj.generatePermutationsWithDuplicates(str);
        cout << endl;

        str = "abc";
        obj.generatePermutationsWithDuplicates(str);
        cout << endl;

        str = "aac";
        obj.getSortedPermutationsWithDuplcates(str);
    }

   private:
    vector<string> permutations(string str) {
        vector<string> result;
        permutations(str, 0, str.length(), result);

        return result;
    }

    void permutations(string str, int idx, int n, vector<string>& result) {
        if (idx > n) return;
        if (idx == n) {
            result.push_back(str);
            return;
        }

        for (int i = idx; i < n; i++) {
            swap(str[idx], str[i]);
            permutations(str, idx + 1, n, result);
            swap(str[idx], str[i]);
        }
    }

   private:
    vector<string> permutations1(string str) {
        vector<string> result;
        permutations1(str, "", result);

        return result;
    }

    void permutations1(string str, string cur, vector<string>& result) {
        if (str.length() == 0) {
            result.push_back(cur);
            return;
        }

        for (int i = 0; i < str.length(); i++) {
            string left = str.substr(0, i);
            string right = str.substr(i + 1);

            string rest = left + right;
            permutations1(rest, cur + str[i], result);
        }
    }

   private:
    vector<string> permutationsUsingSTL(string str) {
        vector<string> result;
        do {
            result.push_back(str);
        } while (next_permutation(str.begin(), str.end()));

        return result;
    }

   private:
    void generatePermutationsWithDuplicates(string& str) {
        generatePermutationsWithDuplicates(str, 0, str.length());
    }

    void generatePermutationsWithDuplicates(string& str, int idx, int n) {
        if (idx == n) {
            cout << str << endl;
            return;
        }

        for (int i = idx; i < n; i++) {
            if (i != idx && str[idx] == str[i]) continue;

            swap(str[idx], str[i]);
            generatePermutationsWithDuplicates(str, idx + 1, n);
            swap(str[idx], str[i]);
        }
    }

   private:
    int ceil(string& str, int i) {
        int idx = i + 1;
        for (int j = i + 1; j < str.length(); j++) {
            if (str[j] > str[i] && str[j] < str[idx]) {
                idx = j;
            }
        }

        return idx;
    }
    void getSortedPermutationsWithDuplcates(string& str) {
        sort(str.begin(), str.end());

        while (true) {
            cout << str << endl;

            int idx = -1;
            for (int i = str.length() - 2; i >= 0; i--) {
                if (str[i] < str[i + 1]) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) break;

            int idx1 = ceil(str, idx);
            swap(str[idx], str[idx1]);
            sort(str.begin() + idx + 1, str.end());
        }
    }
};