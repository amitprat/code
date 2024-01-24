#include "../header.h"

/*
https://careercup.com/question?id=7902674

You are given an array that contains integers. The integers content is such that every integer occurs 3 times in that array leaving one integer that appears only once.
Fastest way to find that single integer
-- using memory.
-- not using any external memory.

eg: [2,1,4,5,1,4,2,2,4,1]

Add the numbers bitwise mod 3. I guess too many people were just saying "XOR" without understanding properly.
*/
class FindNumberOccursOnlyOnce {
   public:
    static void test() {
        FindNumberOccursOnlyOnce obj;
        vector<int> arr = {2, 1, 9, 4, 5, 1, 4, 2, 2, 4, 1, 5, 5};
        cout << obj.findNum(arr) << endl;

        cout << obj.findNum2(arr) << endl;
    }

    // Add the numbers bitwise mod 3. I guess too many people were just saying "XOR" without understanding properly.
    int findNum(vector<int> arr) {
        int res = 0;
        for (int i = 0; i < 32; i++) {  // considering each number is 4 byte
            int cur = 0;
            for (auto num : arr) {
                if (num & (1 << i)) {
                    cur = (cur + 1) % 3;  // sum mod all bits at ith position
                }
            }
            res |= cur << i;  // set the bit value in result
        }

        return res;
    }

    int findNum2(vector<int> arr) {
        int ones = 0;
        int twos = 0;
        int not_threes;
        int x;

        for (int i = 0; i < arr.size(); i++) {
            x = arr[i];
            twos |= ones & x;
            ones ^= x;
            not_threes = ~(ones & twos);
            ones &= not_threes;
            twos &= not_threes;
        }

        return ones;
    }
};