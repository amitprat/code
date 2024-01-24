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
#include <string.h>
using namespace std;

class SubstringCount
{
public:
    static void test()
    {
        SubstringCount obj;
        string src = "abcdefghcde";
        string sub = "cde";

        vector<int> indices = obj.findCount(src, sub);
        cout << "Count : " << indices.size() << endl;
        for (auto i : indices) {
            cout << "Found at index : " << i << ", str : " << src.substr(i, sub.length()) << endl;
        }
    }

    vector<int> findCount(string str, string sub)
    {
        vector<int> result;
        for (int i = 0; i <= str.length() - sub.length(); i++) {
            bool found = true;
            for (int j = i, k = 0; k < sub.length(); j++, k++) {
                if (str[j] != sub[k]) {
                    found = false;  break;
                }
            }
            if (found) {
                result.push_back(i);
            }
        }

        return result;
    }
};
