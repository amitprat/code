package programs.careercup;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class GenerateCombinations {
    public static void test() {
        char[] arr = {'a', '0', 'B', 'c', 'd', 'E'};

        ArrayList<String> result = new ArrayList<>();
        generateCombinations(arr, 0, result);
        System.out.println(result + ", length = " + result.size());

        generateCombinations(arr);
    }

    private static void generateCombinations(char[] arr, int i, ArrayList<String> result) {
        if (i >= arr.length) {
            result.add(new String(arr));
            return;
        }
        generateCombinations(arr, i + 1, result);
        if (Character.isAlphabetic(arr[i])) {
            if (Character.isUpperCase(arr[i]))
                arr[i] = Character.toLowerCase(arr[i]);
            else
                arr[i] = Character.toUpperCase(arr[i]);
            generateCombinations(arr, i + 1, result);
        }
    }

    private static void generateCombinations(char[] arr) {
        Queue<String> res = new LinkedList<>();
        res.add("");
        for (char ch : arr) {
            int n = res.size();
            for (int i = 0; i < n; i++) {
                var curStr = res.poll();
                res.add(curStr + ch);
                if (Character.isAlphabetic(ch)) {
                    var newStr = Character.isUpperCase(ch) ? curStr + Character.toLowerCase(ch)
                            : curStr + Character.toUpperCase(ch);
                    res.add(newStr);
                }
            }
        }
        System.out.println(res + ", length = " + res.size());
    }
}
