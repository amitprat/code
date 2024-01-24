package programs.misc;

import java.util.Arrays;
import java.util.List;

public class RomanToNumeric {
    public static void test() {
        RomanToNumeric obj = new RomanToNumeric();
        List<String> strs = Arrays.asList("XXIV", "XXV", "III", "IV", "VI");

        for (String str : strs) {
            var res = obj.convert(str);
            System.out.println(str + "=>" + res);
        }
    }

    int convert(String str) {
        int next = Integer.MIN_VALUE;
        int response = 0;
        for (int i = str.length() - 1; i >= 0; i--) {
            char ch = str.charAt(i);
            int cur = getDecimal(ch);
            if (next > cur) response -= cur;
            else response += cur;
            next = cur;
        }
        return response;
    }

    int getDecimal(char ch) {
        switch (ch) {
            case 'I':
                return 1;
            case 'V':
                return 5;
            case 'X':
                return 10;
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;
            case 'M':
                return 1000;
            default:
                return 0;
        }
    }
}
