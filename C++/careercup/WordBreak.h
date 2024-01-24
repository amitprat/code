#include "../header.h"

/*
https://careercup.com/question?id=5705581721550848

You're given a dictionary of strings, and a key. Check if the key is composed of an arbitrary number of concatenations of strings from the dictionary. For example:

dictionary: "world", "hello", "super", "hell"
key: "helloworld" --> return true
key: "superman" --> return false
key: "hellohello" --> return true

import java.util.HashSet;

public class ConcantentationOfStrings {
        static String[] dic={"world","hello","super","hell"};


        static boolean isConcantentationOfOtherStrings(String word)
        {
                HashSet<String> hs=new HashSet<String>();

                for(String s: dic) hs.add(s);
                int len=word.length();

                boolean[] table=new boolean[len+1];
                table[0]=true;

                for(int i=0; i < len;i++)
                {
                        for(int j=i; j >= 0;j--)
                        {
                                String subWord=word.substring(j,i+1);
                                if(hs.contains(subWord))
                                {
                                        if(table[j]) table[i+1]=true;
                                }
                        }
                }

                return table[len];
        }
        public static void main(String[] args) {
                // TODO Auto-generated method stub
                System.out.println(isConcantentationOfOtherStrings("hellworld"));

        }

}
*/

// https://www.geeksforgeeks.org/word-break-problem-dp-32/
class WordBreak {
   private:
    bool wordBreakRecursive(string str, unordered_set<string> dict) {
        if (str.empty()) return true;

        for (int i = 1; i <= str.length(); i++) {
            string cur = str.substr(0, i);
            if ((dict.find(cur) != dict.end()) && wordBreakRecursive(str.substr(i), dict)) return true;
        }

        return false;
    }

    bool wordBreakDP(string str, unordered_set<string>& dict) {
        int n = str.length();
        bool table[n + 1] = {false};
        table[0] = true;

        for (int i = 1; i <= n; i++) {
            string first = str.substr(0, i);
            if (!table[i] && dict.find(first) != dict.end()) table[i] = true;

            if (table[i]) {
                for (int j = i + 1; j <= n; j++) {
                    string rest = str.substr(i, j - i);
                    if (!table[j] && dict.find(rest) != dict.end()) table[j] = true;
                }
            }

            if (table[n]) return true;
        }

        return false;
    }

    bool wordBreakDP2(string str, unordered_set<string>& dict) {
        int n = str.length();
        bool table[n + 1] = {false};
        table[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                string cur = str.substr(j, i - j);
                if (table[j] && dict.find(cur) != dict.end()) table[i] = true;
            }
        }

        return table[n];
    }
};