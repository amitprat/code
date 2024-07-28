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
   public:
    static void test() {
        SmallestSubstringContaintingAllCharactersOfSet obj;

        vector<char> set = {'a', 'b', 'c'};
        string str = "abbcbcba";

        auto res = obj.smallestStr(set, str);
        cout << "Result: " << res << endl;
    }

   public:
    string smallestStr(vector<char>& set, string& str) {
        string smallest;

        unordered_map<char, int> patCount;
        for (auto ch : set) patCount[ch]++;

        int curCount = 0;
        unordered_map<char, int> txtCnt;
        int s = 0;
        for (int e = 0; e <= str.size();) {
            if (e < str.size()) {
                char ch = str[e];
                txtCnt[ch]++;
                if (txtCnt[ch] <= patCount[ch]) curCount++;
                e++;
            }

            if (curCount == set.size()) {
                while (txtCnt[str[s]] > patCount[str[s]]) {
                    txtCnt[str[s]]--;
                    s++;
                }

                if (smallest.empty() || e - s < smallest.length()) {
                    smallest = str.substr(s, e - s);
                }

                curCount--;
                txtCnt[str[s]]--;
                s++;
            }

            if (e == str.size() && curCount < set.size()) break;
        }

        return smallest;
    }
};