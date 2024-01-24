package programs.careercup;

import java.util.HashMap;
import java.util.Map;

/*
https://www.careercup.com/question?id=5684278553739264

Given s string, Find max size of a sub-string, in which no duplicate chars present.
 */

public class SubstringWithNoDuplicateChars {
    public static void test() {
        SubstringWithNoDuplicateChars obj = new SubstringWithNoDuplicateChars();

        {
            String str = "geeksforgeeks";

            String res1 = obj.getSubstrWithNoDupChars(str);
            String res2 = obj.longestSubstringUnrepeatedChar(str);
            System.out.println("Result: " + res1);
            System.out.println("Result: " + res2);
        }

        {
            String str = "abracadabra";

            String res1 = obj.getSubstrWithNoDupChars(str);
            String res2 = obj.longestSubstringUnrepeatedChar(str);
            System.out.println("Result: " + res1);
            System.out.println("Result: " + res2);
        }
    }

    private String getSubstrWithNoDupChars(String str) {
        int[] count = new int[256];
        int i = 0;
        String maxStr = "";
        for(int j=0;j<str.length();j++) {
            int ch = (int)(str.charAt(j));
            if(count[ch] != 0) {
                if(j-i > maxStr.length()) maxStr = str.substring(i, j);
                for(int k=i;k<j;k++) {
                    ch = (int)(str.charAt(k));
                    count[ch]--;
                }
                i = j;
            }
            count[ch]++;
        }

        return maxStr;
    }

    private String longestSubstringUnrepeatedChar(String str) {
        Map<Character, Integer> indices = new HashMap<>();
        String longest = "";
        String curMax = "";

        for(int i=0;i<str.length();i++) {
            Character ch = str.charAt(i);
            if(curMax.indexOf(ch) == -1) {
                curMax += ch;
            } else {
                if(curMax.length() > longest.length()) longest = curMax;
                curMax = str.substring(indices.get(ch)+1, i+1);
            }
            indices.put(ch, i);
        }

        return longest;
    }
}
