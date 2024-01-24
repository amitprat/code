package programs.misc;

import java.util.Arrays;
import java.util.List;

public class NumberOfCommonChars {
    public static void test() {
        NumberOfCommonChars obj = new NumberOfCommonChars();
        List<String> input = Arrays.asList("aghkafgklt", "dfghako", "qwemnaarkf");
        System.out.println(obj.count(input));
    }

    int count(List<String> input) {
        int[] cnt = new int[256];
        for (var str : input) {
            int[] tmp = new int[256];
            for (var ch : str.toCharArray()) {
                if (tmp[ch] == 0) {
                    tmp[ch]++;
                    cnt[ch]++;
                }
            }
        }
        int res = 0;
        for (var i : cnt) {
            if (i == input.size()) res++;
        }
        return res;
    }
}
