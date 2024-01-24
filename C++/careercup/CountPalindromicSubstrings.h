#include "../header.h"

class CountPalindromicSubstrings {
    static void test() {
        CountPalindromicSubstrings obj;
        std::string inputString = "ababa";
        int result = obj.countSubstringPalindromes(inputString);
        std::cout << "Total number of substring palindromes: " << result << std::endl;

        return 0;
    }

   private:
    int countSubstringPalindromes(const std::string& inputString) {
        int n = inputString.length();
        int count = 0;

        // Create a 2D DP table to store palindrome information.
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
    int countPalindromicSubstrings(const std::string& s) {
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