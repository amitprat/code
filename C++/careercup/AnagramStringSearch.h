#include "../header.h"

/*
bool anaStrStr (string needle, string haystack)
{
}
Write a function that takes 2 strings , search returns true if any anagram of string1(needle) is present in string2(haystack)

Use the first 26 prime numbers to calculate a hash value for each string window, anagrams of the needle will have the same hash value. E.g., a - 3, b - 5, c - 7, abc has hash value 3*5*7. because the products of prime numbers equal only when have the same prime numbers.
*/

class AnagramStringSearch {
   public:
    static void test() {
        AnagramStringSearch obj;
        string a = "afdgzykxzyxdfyzm";
        string b = "xyz";

        auto res = obj.isSubstr2(a, b);
        cout << "Is substring = " << res << endl;
    }

   public:
    unordered_set<string> findAnagrams(string needle, string haystack) {
        int m = needle.length();
        int n = haystack.length();

        unordered_set<string> result;

        vector<int> primes = getFirstNPrimes(26);
        unsigned long long needleHash = primeProduct(needle, primes);
        unsigned long long hasystackHash = primeProduct(haystack.substr(0, m), primes);

        if (needleHash == hasystackHash)
            result.insert(haystack.substr(0, m));

        for (int i = m; i <= n - m + 1; i++) {
            hasystackHash = updatePrimeProduct(hasystackHash, haystack[i], haystack[i - m], primes);
            if (needleHash == hasystackHash)
                result.insert(haystack.substr(i - m + 1, m));
        }
    }

   private:
    unsigned long long primeProduct(const string& s, const vector<int>& primes) {
        unsigned long long product = 1;
        for (int i = 1; i < s.length(); i++) {
            product *= primes[s[i] - 97];  // 97 considering all characters are upper case.
        }

        return product;
    }

    unsigned long long updatePrimeProduct(unsigned long long key, char add, char remove, vector<int>& primes) {
        return (key / primes[remove - 97]) * (primes[add - 97]);
    }

   private:
    vector<int> getFirstNPrimes(int n) {
        vector<int> primes;
        if (n == 0) return primes;

        primes.push_back(2);
        if (n == 1) return primes;

        for (int p = 3; primes.size() < n; p += 2) {
            if (isPrime(p)) primes.push_back(p);
        }

        return primes;
    }

    bool isPrime(int num) {
        if (num == 1) return false;
        for (int p = 2; p * p <= num; p++) {
            if (p * p == num) return false;
        }

        return true;
    }

   private:
    // approach 2
    bool isSubstr(string a, string b) {
        int n = a.size();
        int m = b.size();

        int* aCount = new int[256];
        int* bCount = new int[256];
        memset(aCount, 0, sizeof(int) * 256);
        memset(bCount, 0, sizeof(int) * 256);

        for (int i = 0; i < m; i++) {
            aCount[a[i]]++;
            bCount[b[i]]++;
        }

        int cnt = 0;
        for (int i = m; i < n; i++) {
            if (isSame(aCount, bCount)) {
                cout << "Found at index = " << (i - m) << " to " << i - 1 << endl;
                return true;
            }

            int oldIndex = i - m;
            aCount[a[oldIndex]]--;
            aCount[a[i]]++;
        }

        if (isSame(aCount, bCount)) {
            cout << "Found at index = " << (n - m) << " to " << n - 1 << endl;
            return true;
        }
        return false;
    }

    bool isSame(int a[], int b[]) {
        for (int i = 0; i < 256; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

   private:
    // approach 3
    bool isSubstr1(string a, string b) {
        int n = a.size();
        int m = b.size();

        int* aCount = new int[256];
        int* bCount = new int[256];
        memset(aCount, 0, sizeof(int) * 256);
        memset(bCount, 0, sizeof(int) * 256);

        for (auto ch : b) bCount[ch]++;

        int count = 0;
        for (int j = 0; j < n; j++) {
            char ch = a[j];
            aCount[ch]++;
            if (aCount[ch] <= bCount[ch]) count++;

            if (count == m) {
                cout << "Found at index = " << (j - m) << " to " << j << endl;
                return true;
            }

            if (j >= m) {
                if (aCount[a[j - m]] <= bCount[a[j - m]]) count--;  // this character was counted above so reduce the count
                aCount[a[j - m]]--;                                 // remove (j-m)th character
            }
        }

        return false;
    }
};