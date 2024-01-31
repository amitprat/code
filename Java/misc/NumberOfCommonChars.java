package Java.misc;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.BitSet;
import java.util.List;
/*
 * https://www.careercup.com/question?id=6283084039192576
 * Write a program that gives count of common characters presented in an array of strings..(or array of character arrays)
 * For eg.. for the following input strings..
 * aghkafgklt
 * dfghako
 * qwemnaarkf
 * The output should be 3. because the characters a, f and k are present in all 3 strings.
 */

public class NumberOfCommonChars {
    public static void test() {
        NumberOfCommonChars obj = new NumberOfCommonChars();
        List<String> input = Arrays.asList("aghkafgklt", "dfghako", "qwemnaarkf");
        System.out.println(obj.countUsingCountHash(input));
    }

    public int countUsingSorting(List<String> input) {
        List<String> sortedStrs = new ArrayList<String>();
        for (var str : input) {
            char[] chars = str.toCharArray();
            Arrays.sort(chars);
            String sorted = new String(chars);
            sortedStrs.add(sorted);
        }

        int[] indices = new int[input.size()];
        int commonChars = 0;
        while (true) {
            int minPos = -1;
            int pos = 0;
            for (var index : indices) {
                if (input.get(pos).length() <= index)
                    break;
                if (minPos == -1 || input.get(minPos).charAt(indices[minPos]) > input.get(pos).charAt(index)) {
                    minPos = pos;
                }
                pos++;
            }
            if (minPos == -1)
                break;
            indices[minPos]++;
            commonChars++;
        }

        return commonChars;
    }

    public int countUsingCountHash(List<String> input) {
        int[] charCount = new int[256];

        for (var str : input) {
            int[] uniqueSet = new int[256];
            for (var ch : str.toCharArray()) {
                if (uniqueSet[ch] == 0) {
                    uniqueSet[ch]++;
                    charCount[ch]++;
                }
            }
        }

        int res = 0;
        for (var i : charCount) {
            if (i == input.size())
                res++;
        }
        return res;
    }

    public int countUsingCountHash2(List<String> input) {
        int[] uniqueSet = new int[256];
        var firstStr = input.get(0);
        for (var ch : firstStr.toCharArray()) {
            uniqueSet[ch]++;
        }
        for (int i = 1; i < input.size(); i++) {
            String cur = input.get(i);
            for (char ch : cur.toCharArray()) {
                if (uniqueSet[ch] > i)
                    continue;
                uniqueSet[ch]++;
            }
        }

        int res = 0;
        for (var i : uniqueSet) {
            if (i == input.size())
                res++;
        }
        return res;
    }

    public int countUsingBitset(List<String> input) {
        BitSet[] bitSetArr = new BitSet[input.size()];
        for (var arr : bitSetArr)
            arr = new BitSet(256);

        int index = 0;
        for (var str : input) {
            for (var ch : str.toCharArray()) {
                bitSetArr[index].set((int) ch);
                ;
            }
            index++;
        }

        int unique = 0;
        for (int i = 1; i < input.size(); i++) {
            bitSetArr[0].and(bitSetArr[i]);
        }
        for (int i = 0; i < 256; i++) {
            if (bitSetArr[0].get(i))
                unique++;
        }

        return unique;
    }
}
