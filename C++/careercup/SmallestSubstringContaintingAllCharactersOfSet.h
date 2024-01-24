#include "../header.h"

/*
https://careercup.com/question?id=5092414932910080

You are given a set of unique characters and a string.

Find the smallest substring of the string containing all the characters in the set.

ex:
Set : [a, b, c]
String : "abbcbcba"

Result: "cba"


public String findMin (String s, HashSet<Character> set){
    int len = set.size() , count = 0 , tail = 0 , minLen = Integer.MAX_VALUE;
    String result = "" ;
    HashMap<Character, Integer> map = new HashMap<> ();
    for (int i = 0 ; i < s.length() ; ++i) {
        char ch = s.charAt(i) ;
        if (set.contains(ch)) {
            int c = map.containsKey(ch) ? map.get(ch) + 1 : 1 ;
            if (c == 1) count++;
            map.put(ch, c) ;
        }
        while (count == len) {
            if (set.contains(s.charAt(tail))) {
                int v = map.get(s.charAt(tail));
                if (v - 1 == 0) {
                        count--;
                }
                map.put(s.charAt(tail), v - 1) ;
            }
            if (i - tail + 1 < minLen) {
                minLen = i - tail + 1 ;
                result = s.substring(tail, i + 1) ;
            }
            tail++;
        }
    }
    return result;
}
*/
class SmallestSubstringContaintingAllCharactersOfSet {
};