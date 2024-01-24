#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Count2s
{
public:
    static void test()
    {
        Count2s obj;
        vector<int> v = { 0,1,2,4,9,10 ,11, 12, 19, 81, 99, 101, 189, 250, 522, 989, 1001 };
        for (auto i : v) {
            cout << "2s count in " << i << " = " << obj.countBruteforce(i) << endl;
        }
    }

    int countBruteforce(int n) {
        int res = 0;
        for (int i = 2; i <= n; i++) {
            res += count2Util(i);
        }

        return res;
    }

    int count2Util(int n) {
        int res = 0;
        while (n) {
            if (n % 10 == 2) res++;
            n /= 10;
        }

        return res;
    }

    int count2s(int n)
    {
        int mul = 1;
        while (n / mul) mul *= 10;
        mul /= 10;

        if (n / mul < 2) return counts(mul) + count(n % mul);
        else if (n / mul == 2) {
            return (n - mul * 2) + 2 * counts(mul);
        }
        else {
            return mul + (n / mul) * count(mul);
        }
    }
};