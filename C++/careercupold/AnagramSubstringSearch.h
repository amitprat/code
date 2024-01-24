#pragma once
#include "../Header.h"

class AnagramSubstringSearch {
public:
    static void test() {
        AnagramSubstringSearch obj;
        string a = "afdgzykxzyxdfyzm";
        string b = "xyz";

        auto res = obj.isSubstr2(a, b);
        cout << "Is substring = " << res << endl;
    }

    bool isSubstr(string a, string b) {
        int* aCount = new int[256];
        int* bCount = new int[256];
        memset(aCount, 0, sizeof(int) * 256);
        memset(bCount, 0, sizeof(int) * 256);

        for (int i = 0; i < b.size(); i++) {
            aCount[a[i]]++;
            bCount[b[i]]++;
        }
        int cnt = 0;

        for (int i = b.size(); i < a.size(); i++) {
            if (isSame(aCount, bCount)) {
                cout << "Found at index = " << (i - b.size()) << " to " << i - 1 << endl;
                return true;
            }
            int oldIndex = i - b.size();
            aCount[a[oldIndex]]--;
            aCount[a[i]]++;
        }
        if (isSame(aCount, bCount)) {
            cout << "Found at index = " << (a.size() - b.size()) << " to " << a.size() - 1 << endl;
            return true;
        }
        return false;
    }

    bool isSubstr1(string src, string dst) {
        int* srcCount = new int[256];
        int* dstCount = new int[256];
        memset(srcCount, 0, sizeof(int) * 256);
        memset(dstCount, 0, sizeof(int) * 256);

        int count = 0;
        for (int i = 0; i < dst.size(); i++) dstCount[dst[i]]++;
        for (int i = 0; i < dst.size() - 1; i++) {
            srcCount[src[i]]++;
            if (srcCount[src[i]] <= dstCount[src[i]]) count++;
        }
        for (int i = dst.size() - 1; i < src.size(); i++) {
            srcCount[src[i]]++;
            if (srcCount[src[i]] <= dstCount[src[i]]) count++;
            if (count == dst.size()) {
                cout << "Found at index = from " << (i - dst.size() + 1) << " to " << i << endl;
                return true;
            }
            srcCount[src[i - dst.size() + 1]]--;
        }
        return false;
    }

    bool isSubstr2(string src, string pat)
    {
        vector<int> srcCnt(256, 0);
        vector<int> patCnt(256, 0);
        int cnt = 0;
        int n = src.length(), m = pat.length();

        for (int i = 0; i < m; i++) patCnt[pat[i]]++;

        bool found = false;
        int i = 0;
        for (int j = 0; j < n; j++)
        {
            srcCnt[src[j]]++;
            if (srcCnt[src[j]] <= patCnt[src[j]]) cnt++;

            if (cnt == m)
            {
                while (i <= j && srcCnt[src[i]] > patCnt[src[i]]) i++;
                if (j - i + 1 == m) {
                    cout << "Anagram found at " << i << " to " << j << " = " << src.substr(i, j - i + 1) << endl;
                    found = true;
                }
                cnt--;
                srcCnt[src[i]]--;
                i++;
            }
        }

        return found;
    }
private:
    bool isSame(int a[], int b[]) {
        for (int i = 0; i < 256; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
};