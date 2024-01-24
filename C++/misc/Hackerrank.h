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
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class Hackerrank
{
public:
    static void test()
    {
        Hackerrank rank;
        {
            vector<int> v = { 5,1,2,8,5,6,2 };
            auto res = rank.findSubsequence(v, 2);
            for (auto i : res) {
                cout << i << " ";
            }
            cout << endl;
        }

        {
            vector<int> v = { 4,6, 24,12,1,4 };
            auto res = rank.findSubsequence(v, 4);
            for (auto i : res) {
                cout << i << " ";
            }
            cout << endl;
        }

        {
            vector<int> v = { 5,4,15,20,1 };
            auto res = rank.findSubsequence(v, 3);
            for (auto i : res) {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    int gcd(int a, int b)
    {
        if (!a) return b;
        if (!b) return a;
        return gcd(b, a % b);
    }
    vector<int> findSubsequence(vector<int> numbers, int k) {
        int maxgcd = INT_MIN;
        vector<int> result;

        for (int i = 0; i < numbers.size(); i++) {
            int curgcd = numbers[i];
            vector<int> subseq;
            subseq.push_back(numbers[i]);
            for (int j = i + 1; j < numbers.size(); j++) {
                int newgcd = gcd(curgcd, numbers[j]);
                if (newgcd > maxgcd) {
                    subseq.push_back(numbers[j]);
                    curgcd = min(curgcd, newgcd);
                }
            }
            cout << maxgcd << " " << curgcd << endl;
            if (subseq.size() >= k && curgcd > maxgcd) {
                maxgcd = curgcd;
                result = subseq;
            }
        }

        return result;
    }
};