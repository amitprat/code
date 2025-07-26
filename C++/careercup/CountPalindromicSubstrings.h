#include "../header.h"

class CountPalindromicSubstrings {
   public:
    static void test() {
        CountPalindromicSubstrings obj;

        auto strs = {"abc", "aba", "a", "aa", "aaa", "aca", "bba", "bac", "ababa"};
        for (auto& str : strs) {
            int result1 = obj.countSubstringPalindromes1(str);
            int result2 = obj.countSubstringPalindromes2(str);
            int result3 = obj.countSubstringPalindromes3(str);
            assert(result1 == result2);
            assert(result1 == result3);

            println("Total number of palindromes in string:{} are {}", str, result1);
        }
    }

   private:
    int countSubstringPalindromes1(const std::string& str) {
        int n = str.length();
        int count = 0;
        std::vector<std::vector<bool>> table(n, std::vector<bool>(n, false));

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                if (len == 1) table[i][j] = true;
                else if (len == 2) table[i][j] = (str[i] == str[j]);
                else if (str[i] == str[j]) table[i][j] = table[i + 1][j - 1];
                if (table[i][j]) count++;
            }
        }

        return count;
    }

   private:
    int countSubstringPalindromes2(const std::string& inputString) {
        int n = inputString.length();
        int count = 0;
        std::vector<std::vector<bool>> isPalindrome(n, std::vector<bool>(n, false));

        // All individual characters are palindromes.
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
            count++;
        }

        // Check for palindromic substrings of length 2 or more.
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                // A substring is a palindrome if its inner substring is also a palindrome and the outer characters match.
                if (inputString[i] == inputString[j] && (len == 2 || isPalindrome[i + 1][j - 1])) {
                    isPalindrome[i][j] = true;
                    count++;
                }
            }
        }

        return count;
    }

   private:
    int countSubstringPalindromes3(const std::string& s) {
        int count = 0;
        int n = s.length();

        // Function to expand around a center.
        auto expandAroundCenter = [&](int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
        };

        for (int i = 0; i < n; i++) {
            // Odd-length palindromes with center at i.
            expandAroundCenter(i, i);

            // Even-length palindromes with centers at i and i+1.
            expandAroundCenter(i, i + 1);
        }

        return count;
    }
};