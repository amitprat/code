#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=5726326363783168
* 
facebook-interview-questions1
of 1 vote
33
Answers
Given an integer 'n', create an array such that each value is repeated twice. For example

n = 3 --> [1,1,2,2,3,3]
n = 4 --> [1,1,2,2,3,3,4,4]

After creating it, find a permutation such that each number is spaced in such a way, they are at a "their value" distance from the second occurrence of the same number.

For example: n = 3 --> This is the array - [1,1,2,2,3,3]

Your output should be [3,1,2,1,3,2]

The second 3 is 3 digits away from the first 3.
The second 2 is 2 digits away from the first 2.
The second 1 is 1 digit away from the first 1.

Return any 1 permutation if it exists. Empty array if no permutation exists.

Follow up: Return all possible permutations.
*/
class GenerateSeq {
public:
    static void test() {

        for (int n = 1; n <= 10; n++) {
            cout << "Generating for n = " << n << endl;
            vector<int> result(2 * n, 0);
            unordered_set<int> included;
            auto res = generate(n, result, included, n);

            if (res) cout << to_string(result) << endl;
        }
    }

    static bool generate(int n, vector<int>& result, unordered_set<int>& included, int rem) {
        if (rem == 0) return true;

        for (int i = n; i >= 1; i--) {
            if (included.find(i) != included.end()) continue;
            for (int j = 0; j + i + 1 < 2 * n; j++) {
                if (result[j] != 0 || result[j + i + 1] != 0) continue;
                result[j] = result[j + i + 1] = i;
                included.insert(i);
                if (generate(n, result, included, rem - 1)) return true;
                included.erase(i);
                result[j] = result[j + i + 1] = 0;
            }
        }

        return false;
    }
};