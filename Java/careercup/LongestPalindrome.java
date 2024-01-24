package programs.careercup;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class LongestPalindrome {
    public static void test() {
        LongestPalindrome obj = new LongestPalindrome();
        {
            var res = obj.longestPalin("aha");
            var expected = "aha";
            System.out.println("Actual " + res + ", Expected " + expected);
        }
        {
            var res = obj.longestPalin("ttaatta");
            var expected = "ttaaatt";
            System.out.println("Actual " + res + ", Expected " + expected);
        }
        {
            var res = obj.longestPalin("abc");
            var expected = "a";
            System.out.println("Actual " + res + ", Expected " + expected);
        }
        {
            var res = obj.longestPalin("gggaaa");
            var expected = "aggga";
            System.out.println("Actual " + res + ", Expected " + expected);
        }
    }

    private String fill(int length, char ch) {
        char[] array = new char[length];
        Arrays.fill(array, ch);
        return new String(array);
    }

    private String longestPalin(String str) {
        Map<Character, Integer> counter = new HashMap<>();
        for (char ch : str.toCharArray()) {
            if (!counter.containsKey(ch)) counter.put(ch, 0);
            counter.put(ch, counter.get(ch) + 1);
        }

        StringBuilder half = new StringBuilder();
        Character center = null;

        for (var entry : counter.entrySet()) {
            int div = entry.getValue() / 2;
            half.append(fill(div, entry.getKey()));
            int rem = entry.getValue() % 2;
            if (rem != 0) {
                //if (center != null) return "";
                center = entry.getKey();
            }
        }

        return half.toString() + center + half.reverse();
    }
}
