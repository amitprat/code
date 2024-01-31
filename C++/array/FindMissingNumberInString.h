#pragma once
#include "../header.h"

class FindMissingNumberInString {
   public:
    static void test() {
        vector<string> inputs = {"9810", "9799", "9799980098029803", "9799100101102", "979899100101102", "979899100101103"};
        for (const auto& str : inputs) {
            int num = findMissingNumber(str);
            cout << format("Find missing number in {} is {}.", str, num) << endl;
        }
    }

   private:
    static int findMissingNumber(string str) {
        int n = str.size();

        // assume the max length of an integer number is <= 7
        for (int i = 1; i <= n && i <= 7; i++) {
            int curNum = stoi(str.substr(0, i));  // consider i digit number starting from 0 index

            int missingNum = -1;
            int j = i;
            while (j + len(curNum + 1) <= n) {
                int nextNum = stoi(str.substr(j, len(curNum + 1)));

                if (nextNum == curNum + 1) {
                    curNum = nextNum;
                } else if (nextNum == curNum + 2 && missingNum == -1) {
                    missingNum = curNum + 1;
                    curNum = nextNum;
                } else {
                    break;
                }

                j += len(nextNum);
            }

            if (j == n) return missingNum == -1 ? curNum + 1 : missingNum;
        }

        return -1;
    }

    static int len(int num) {
        return (int)(log10(num)) + 1;
    }
};
