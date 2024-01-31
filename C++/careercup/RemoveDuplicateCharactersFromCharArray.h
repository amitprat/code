#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=5680831603408896

Java: You're given a very large array of char's.
Write a method to remove duplicates in the array, in place. Optimize for space complexity, not time complexity.
*/
class RemoveDuplicateCharactersFromCharArray {
   public:
    static void test() {
        string arr = "ABCEFGABCXYZ";
        char* charArr = const_cast<char*>(arr.c_str());

        RemoveDuplicateCharactersFromCharArray obj;
        obj.removeDuplicateCharacters(charArr);

        cout << charArr << endl;
    }

   public:
    void removeDuplicateCharacters(char arr[]) {
        int tail = 0;
        bitset<256> set;
        int n = strlen(arr);

        for (int head = 0; head < n; head++) {
            char ch = arr[head];

            if (!set[(int)ch]) {
                arr[tail++] = ch;
                set.set((int)ch, true);
            }
        }

        for (; tail < n; tail++) {
            arr[tail] = '\0';
        }
    }
};