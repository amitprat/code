package programs.string;

import java.util.Arrays;
import java.util.List;

/*
You are given a string S and a set of n substrings. You are supposed to remove every instance of those n substrings from S so that S is of the minimum length and output this minimum length.
Eg:
S- ccdaabcdbb
n=2 - substrings-- ab, cd
Output: 2
Explanation:
ccdaabcdbb -> ccdacdbb -> cabb -> cb (length=2)
Can someone help me with the algo?
 */
public class ReduceString {
    public static void test() {
        ReduceString obj = new ReduceString();
        String input = "ccdaabcdbb";
        List<String> substrs = Arrays.asList("ab", "cd");
        System.out.println(obj.reduceString(input, substrs));
    }

    private String reduceString(String input, List<String> substrs) {
        int mxLen = 0;
        for (var str : substrs) {
            mxLen = Math.max(mxLen, str.length());
        }

        char[] arr = input.toCharArray();
        for (int i = 0; i < input.length(); i++) {
            int s = formsSubstr(arr, i, substrs, mxLen);
            if (s != -1) {
                for (int j = s; j <= i; j++) {
                    arr[j] = '$';
                }
            }
        }
        int i = 0, j = 1;
        while (j < arr.length) {
            if (arr[j] != '$') {
                swap(arr, i, j);
                i++;
            }
            j++;
        }
        return new String(arr, 0, i + 1);
    }

    private int formsSubstr(char[] arr, int end, List<String> substrs, int mxLen) {
        int start = end;
        while (start >= 0 && end - start + 1 <= mxLen) {
            String tmp = new String(arr, start, end - start + 1);
            for (var str : substrs) if (str.equals(tmp)) return start;
            start--;
        }
        return -1;
    }

    private void swap(char[] arr, int s, int e) {
        char tmp = arr[s];
        arr[s] = arr[e];
        arr[e] = tmp;
    }
}
