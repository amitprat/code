#include "../header.h"

/*
https://careercup.com/question?id=5671785349513216

// cat, actor -> T
// car, actor -> F

bool anaStrStr (string needle, string haystack)
{
}
Write a function that takes 2 strings , search returns true if any anagram of string1(needle) is present in string2(haystack)

Use the first 26 prime numbers to calculate a hash value for each string window,
anagrams of the needle will have the same hash value. E.g., a - 3, b - 5, c - 7, abc has hash value 3*5*7.
because the products of prime numbers equal only when have the same prime numbers.

This solution is easier than the one I posted earlier

List<String> FindAnagrams(String needle, String haystack){
  int m = needle.length();
  int n = haystack.length();

  HashSet<String> h = new HashSet<String>();
  int hashKey = PrimeProduct(needle);
  int key = PrimeProduct(hayStack.subString(0, m-1);
  if(key == hashKey)
    h.add(hayStack.subString(0, m-1));

  for(int i = m, i<= n - 1 - m; i++){
    int key = UpdatePrimeProduct(haystack.charAt[i+m-1], haystack.charAt[i], key);
        if(key == hashKey)
          h.add(haystack.subString(i, i+m-1));
  }
}

UpdatePrimeProduct(char add, char remove){
  return key/remove*add;
}

PrimeProduct(String s, int[] prime){
  int diff = 97;
  int product = 1;
  for(int i= 1; i< s.length(); i++){
    product *= prime[(int)s.charAt[i] - 97]
  }

  return product;
}

This is how to generate the first 26 prime numbers:


int[] GenerateNPrimeNumbers(int n){
  int[] p = new int[n+1]{};
  P[0] = 2;
  int i = 1; // # of found prime numbers
  int num = 1;// start checking from the next odd number of 3

  while(i < n){
    num+= 2;// get the next odd number
    boolean isPrime = true;
    int j = 1; // skip 1

    // check all prime numbers that are smaller than num squre
    while(p[j] <= Math.sqr(num)){
        if(num/p[j] == 0){
          isPrime = false;
          break;
        }

        j++;
    }

    if(isPrime){
     p[i] = num;
     i++;
    }
  }

  return p;
}
*/
class SearchAnagramOfWordInHaystack {
   public:
    vector<string> anagrams(const string& haystack, const string& needle) {
        vector<int> txtCnt(256, 0);
        vector<int> patCnt(256, 0);

        int n = haystack.size();
        int m = needle.size();

        for (int i = 0; i < n && i < m; i++) {
            txtCnt[haystack[i]]++;
            patCnt[needle[i]]++;
        }

        vector<string> result;
        if (isSame(txtCnt, patCnt)) result.push_back(haystack.substr(0, m));

        for (int i = m; i < n; i++) {
            char oldch = haystack[i - m];
            char newch = haystack[i];

            txtCnt[oldch]--;
            txtCnt[newch]++;

            if (isSame(txtCnt, patCnt)) result.push_back(haystack.substr(i - m + 1, m));
        }

        return result;
    }

    bool isSame(const vector<int>& txtCnt, const vector<int>& patCnt) {
        for (int i = 0; i < 256; i++) {
            if (txtCnt[i] != patCnt[i]) return false;
        }
        return true;
    }

   private:
    vector<string> findAnagrams(const string& txt, const string& pat) {
        vector<string> result;
        vector<int> primes = generateNPrimeNums(256);

        int n = txt.size();
        int m = pat.size();

        long txtHash = primeProduct(txt.substr(0, m), primes);
        long patHash = primeProduct(pat, primes);

        if (txtHash == patHash) result.push_back(txt.substr(0, m));

        for (int i = m; i < n; i++) {
            txtHash = update(txtHash, primes, txt[i - m], txt[i]);
            if (txtHash == patHash) result.push_back(txt.substr(i - m + 1, m));
        }

        return result;
    }

    long primeProduct(const string& s, const vector<int>& primes) {
        long prod = 1;
        long diff = 97;

        for (int i = 0; i < s.length(); i++) {
            int ch = (int)s[i];
            prod *= primes[ch - diff];
        }

        return prod;
    }

    long update(long curHash, const vector<int>& primes, char remove, char add) {
        return (curHash / primes[remove]) * primes[add];
    }

    vector<int> generateNPrimeNums(int n) {
        vector<int> result;
        if (n >= 1) result.push_back(2);

        int num = 3;
        while (result.size() < n) {
            if (isPrime(num)) result.push_back(num);
            num += 2;
        }

        return result;
    }

    bool isPrime(int num) {
        if (num < 2) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;

        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2)) return false;
        }
        return true;
    }
};