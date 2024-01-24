#include "../Header.h"

/*
bool anaStrStr (string needle, string haystack) 
{
}
Write a function that takes 2 strings , search returns true if any anagram of string1(needle) is present in string2(haystack)
*/

/*
Use the first 26 prime numbers to calculate a hash value for each string window, anagrams of the needle will have the same hash value. E.g., a - 3, b - 5, c - 7, abc has hash value 3*5*7. because the products of prime numbers equal only when have the same prime numbers.

This solution is easier than the one I posted earlier
*/

List<String> FindAnagrams(String needle, String haystack)
{
    int m = needle.length();
    int n = haystack.length();

    HashSet<String> h = new HashSet<String>();
    int hashKey = PrimeProduct(needle);
    int key = PrimeProduct(hayStack.subString(0, m-1);
    if(key == hashKey)
      h.add(hayStack.subString(0, m-1));
    
    for(int i = m, i<= n - 1 - m; i++){
          int key = UpdatePrimeProduct(haystack.charAt[i + m - 1], haystack.charAt[i], key);
          if (key == hashKey)
              h.add(haystack.subString(i, i + m - 1));
    }
}

UpdatePrimeProduct(char add, char remove)
{
    return key / remove * add;
}

PrimeProduct(String s, int[] prime)
{
    int diff = 97;
    int product = 1;
    for (int i = 1; i < s.length(); i++)
    {
        product *= prime[(int)s.charAt[i] - 97]
    }

    return product;
}