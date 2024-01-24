#include "../header.h"

/*
https://careercup.com/question?id=5158272756613120

Given a string, find the longest substring with k distinct characters.

e.g - “aaaabbbb”, k = 2, “aaaabbbb”
“asdfrttt” k = 3, “asd”, “frttt”

[Telephonic Question]

This problem can be solved with TWO POINTERS that make a sliding window and a map to store occurrence of the distinct characters in the window.

public static String longestSubstringWithKDistinctChars(String s, int k) {
    int left = 0, right = 0;        //create a window for substring(left, right + 1)
    Map<Character, Integer> distinctChars = new HashMap<>();  // store occurrence of chars in the window
    String max = "";   // the output
    while(right < s.length()) {
        char c = s.charAt(right);
        distinctChars.put(c, distinctChars.getOrDefault(c, 0) + 1);
        right++;

        if(distinctChars.size() == k) {             //if window size == k, compare length of current substring with max
            if(right - left + 1 > max.length()) {
                max = s.substring(left, right + 1);  //if current substring is longer, replace max with current
            }
        }

        while(distinctChars.size() == k + 1) {      //if window size > k, discard the char on the left
            char toRemove = s.charAt(left);
            if(distinctChars.get(toRemove) == 1) {
                distinctChars.remove(toRemove);
            } else {
                distinctChars.put(toRemove, distinctChars.get(toRemove) - 1);
            }
            left++;
        }
    }

    return max;
}
*/
class LongestSubstringWithKDistinctChars {
};