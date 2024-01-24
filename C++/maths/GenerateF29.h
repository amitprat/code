#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class GenerateF29
{
public:
    static void test()
    {
        srand(time(NULL));
        GenerateF29 obj;
        cout << "Output: {";
        for (int i = 0; i < 32; i++) {
            cout << obj.f29() << ", ";
        }
        cout << "}" << endl;
    }

    int f29()
    {
        int radix = 2;
        int res;
        do {
            res = f1() * pow(radix, 4) + f1() * pow(radix, 3) + f1() * pow(radix, 2) + f1() * pow(radix, 1) + f1();
        } while (res > 29);

        return res;
    }

    int f1()
    {
        return rand() % 2;
    }
};