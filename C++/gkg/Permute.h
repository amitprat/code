#pragma once
#include "../Header.h"

class Permute {
public:
    static void test() {
        string str = "ACBC";
        permute_stl(str, 0, str.length());
    }

    static void permute(string& str, int i, int n) {
        if (i == n) {
            cout << str << " ";
            return;
        }

        for (int j = i; j < n; j++) {
            swap(str[i], str[j]);
            permute(str, i + 1, n);
            swap(str[i], str[j]);
        }
    }

    static void permute_stl(string str, int i, int n) {
       // sort(str.begin(), str.end());
        do {
            cout << str << " ";
        } while (next_permutation(str.begin(), str.end()));
    }

    static void permute_withoutdup(string str, int i, int n) {
        sort(str.begin(), str.end());
        do {
            cout << str << " ";
        } while (nextPermutation(str));
    }

    static bool nextPermutation(string& str) {
        int s = str.length() - 2;
        while (s >= 0 && str[s] >= str[s + 1]) s--;

        if (s < 0) return false;

        int e = s + 1;
        for (int i = e + 1; i < str.length(); i++) {
            if (str[i] < str[e] && str[i] > str[s]) e = i;
        }

        swap(str[s], str[e]);

        sort(str.begin() + s + 1, str.end());

        return true;
    }
};