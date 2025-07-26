#pragma once
#include "../header.h"

/*
Write a function that takes 2 strings, returns true if any anagram of string2 (needle)
is present in string1 (haystack).

Use the first 26 prime numbers to calculate a hash value for each string window.
Anagrams of the needle will have the same hash value.
Example: a - 3, b - 5, c - 7 → "abc" has hash = 3*5*7
Because products of primes are unique for a given multiset of characters.
*/

class AnagramStringSearch {
   public:
    static void test() {
        AnagramStringSearch obj;
        string haystack = "afdgzykxzyxdfyzm";
        string needle = "xyz";

        bool res = obj.isSubstr2(haystack, needle);
        cout << "Is substring = " << boolalpha << res << endl;
    }

   public:
    // ✅ Prime product–based search for all anagram matches
    unordered_set<string> findAnagrams(const string& haystack, const string& needle) {
        int n = haystack.length();
        int m = needle.length();
        unordered_set<string> result;

        if (m > n || m == 0) return result;

        vector<int> primes = getFirstNPrimes(26);
        unsigned long long needleHash = primeProduct(needle, primes);
        unsigned long long windowHash = primeProduct(haystack.substr(0, m), primes);

        if (needleHash == windowHash) result.insert(haystack.substr(0, m));

        // ✅ Corrected loop: iterate remaining windows
        for (int i = m; i < n; i++) {
            windowHash = updatePrimeProduct(windowHash, haystack[i], haystack[i - m], primes);
            if (needleHash == windowHash) result.insert(haystack.substr(i - m + 1, m));
        }

        return result;
    }

   private:
    // ✅ Compute prime product for a given string
    unsigned long long primeProduct(const string& s, const vector<int>& primes) {
        unsigned long long product = 1;
        for (char ch : s) {
            product *= primes[ch - 'a'];  // assumes lowercase
        }
        return product;
    }

    // ✅ Update product when sliding window
    unsigned long long updatePrimeProduct(unsigned long long key, char add, char remove, const vector<int>& primes) {
        return (key / primes[remove - 'a']) * primes[add - 'a'];
    }

    // ✅ Generate first N prime numbers
    vector<int> getFirstNPrimes(int n) {
        vector<int> primes;
        if (n <= 0) return primes;

        primes.push_back(2);
        for (int num = 3; primes.size() < n; num += 2) {
            if (isPrime(num)) primes.push_back(num);
        }
        return primes;
    }

    bool isPrime(int num) {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

   private:
    // ✅ Approach 2 – sliding window with frequency arrays
    bool isSubstr(string a, string b) {
        int n = a.size();
        int m = b.size();
        if (m > n) return false;

        vector<int> aCount(256, 0), bCount(256, 0);
        for (int i = 0; i < m; i++) {
            aCount[a[i]]++;
            bCount[b[i]]++;
        }

        for (int i = m; i < n; i++) {
            if (isSame(aCount, bCount)) {
                cout << "Found at index = " << (i - m) << " to " << (i - 1) << endl;
                return true;
            }
            aCount[a[i]]++;
            aCount[a[i - m]]--;
        }

        if (isSame(aCount, bCount)) {
            cout << "Found at index = " << (n - m) << " to " << (n - 1) << endl;
            return true;
        }
        return false;
    }

    bool isSame(const vector<int>& a, const vector<int>& b) {
        for (int i = 0; i < 256; i++)
            if (a[i] != b[i]) return false;
        return true;
    }

   private:
    // ✅ Approach 3 – optimized character counting sliding window
    bool isSubstr1(string a, string b) {
        int n = a.size();
        int m = b.size();
        if (m > n) return false;

        vector<int> aCount(256, 0), bCount(256, 0);
        for (auto ch : b) bCount[ch]++;

        int count = 0;
        for (int j = 0; j < n; j++) {
            char ch = a[j];
            aCount[ch]++;
            if (aCount[ch] <= bCount[ch]) count++;

            if (count == m) {
                cout << "Found at index = " << (j - m + 1) << " to " << j << endl;
                return true;
            }

            if (j >= m - 1) {
                if (aCount[a[j - m + 1]] <= bCount[a[j - m + 1]]) count--;
                aCount[a[j - m + 1]]--;
            }
        }

        return false;
    }

   public:
    // ✅ unified test function calling prime-based approach
    bool isSubstr2(const string& haystack, const string& needle) {
        auto result = findAnagrams(haystack, needle);
        for (auto& s : result) {
            cout << "Found anagram: " << s << endl;
        }
        return !result.empty();
    }
};
