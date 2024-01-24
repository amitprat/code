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

class ReplaceSpace
{
public:
    static void test()
    {
        ReplaceSpace obj;
        int totalSpace = 20;
        char* str = new char[totalSpace];
        memset(str, '\0', sizeof(char) * totalSpace);
        strcpy_s(str, 10, "I am amit");
        str[10] = '\0';

        cout << "Original : " << str << endl;
        char* res = obj.replace(str, totalSpace, "%20");
        cout << "Modified : " << res << endl;
    }

    char* replace(char* str, int totalSpace, string sub)
    {
        int sl = strlen(str);
        int l = sub.length();
        int spaceCount = findSpaceCount(str);
        int extraSpaceReq = (l - 1) * spaceCount;

        char* newArr = str;
        int newLength = sl + extraSpaceReq;
        if (newLength > totalSpace) {
            newArr = new char[newLength + 1];
            memset(newArr, '\0', (newLength + 1) * sizeof(char));
        }
        for (int i = sl - 1, k = newLength - 1; i >= 0; i--) {
            if (str[i] == ' ') {
                for (int j = l - 1; j >= 0; j--) {
                    newArr[k--] = sub[j];
                }
            }
            else {
                newArr[k--] = str[i];
            }
        }

        return newArr;
    }

    int findSpaceCount(char* str) {
        int spaceCount = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == ' ') {
                spaceCount++;
            }
        }
        return spaceCount;
    }
};