#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=5659801074794496

Problem: Number to Alphabet Encodings
--------------------------------------
Given a numeric string, count the number of ways to decode it where:
- '1' -> 'a', '2' -> 'b', ..., '26' -> 'z'

Example:
  Input: "123"
  Output: 3  ("abc", "aw", "lc")

  Input: "1234"
  Output: 3  ("abcd", "lcd", "awd")

Approach:
- Recursively try to take 1 or 2 digits and validate if they're within [1,26].
- Memoize intermediate results for optimization.

bool isValid(string s){
        istringstream ibuf(s);
        int num;
        ibuf >> num;
        if(num>=1 && num <=26)
                return true;
        else
                return false;
}
int numEncoding(string s){
        if(s.length()==0) return 1;
        if(s.length()==1) return 1;

        int num = 0;
        num += numEncoding(s.substr(1));
        if(isValid(s.substr(0,2))) num += numEncoding(s.substr(2));
        return num;
}
*/

class ValidEncodingOfNumberToAlphabets {
   public:
    static void test() {
        vector<string> inputs = {"123", "1234", "10", "26", "101", "27", "0", "301"};

        for (const auto& s : inputs) {
            int res1 = numEncodings1(s);
            int res2 = numEncodings2(s);
            int res3 = numEncodingsWithMemo(s);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("Input='{}' -> Ways: {}", s, res1) << endl;
        }
    }

   public:
    /**
     * Check if a numeric substring is a valid alphabet code (1-26).
     */
    static bool isValid(const string& s) {
        if (s.empty() || s[0] == '0') return false;  // leading zeros are invalid
        int num = stoi(s);
        return num >= 1 && num <= 26;
    }

   public:
    /**
     * Count the number of valid alphabet decodings for a numeric string.
     * Time: O(2^n), no memoization
     */
    static int numEncodings1(const string& s) {
        if (s.empty()) return 1;
        if (s.length() == 1) return isValid(s) ? 1 : 0;

        int num = 0;
        if (isValid(s.substr(0, 1))) num += numEncodings1(s.substr(1));
        if (isValid(s.substr(0, 2))) num += numEncodings1(s.substr(2));
        return num;
    }

   public:
    static int numEncodings2(const string& s) {
        return numEncodingsInner(s, 0);
    }

    static int numEncodingsInner(const string& s, int index) {
        if (index > s.length() || s[index] == '0') return 0;
        if (index == s.length()) return 1;

        int enc = numEncodingsInner(s, index + 1);
        if (index < s.length() - 1 && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) enc += numEncodingsInner(s, index + 2);

        return enc;
    }

   public:
    static int numEncodingsWithMemo(const std::string& s) {
        std::unordered_map<int, int> memo;
        return numEncodingsWithMemoInner(s, 0, memo);
    }

    static int numEncodingsWithMemoInner(const std::string& s, int index, std::unordered_map<int, int>& memo) {
        if (index == s.length()) return 1;
        if (index > s.length() || s[index] == '0') return 0;

        if (memo.count(index)) return memo[index];

        int count = 0;

        // 1-digit decoding
        count += numEncodingsWithMemoInner(s, index + 1, memo);

        // 2-digit decoding
        if (index + 1 < s.length()) {
            int num = (s[index] - '0') * 10 + (s[index + 1] - '0');
            if (num >= 10 && num <= 26) {
                count += numEncodingsWithMemoInner(s, index + 2, memo);
            }
        }

        memo[index] = count;
        return count;
    }
};
