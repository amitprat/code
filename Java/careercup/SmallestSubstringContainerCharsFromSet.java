package programs.careercup;

public class SmallestSubstringContainerCharsFromSet {
    public static void test() {
        char[] set = {'a', 'b', 'c'};
        String str = "abbcbcba";

        var res = subsetString(str, set);
        System.out.println(res);
    }

    private static String subsetString(String str, char[] set) {
        int[] freq = new int[26];
        for (char ch : set) freq[ch - 'a']++;
        int n = set.length;
        int cnt = 0;
        int start = 0;

        int[] curFreq = new int[26];
        int index = 0;
        String res = "";
        for (char ch : str.toCharArray()) {
            if (freq[ch - 'a'] == 0) continue;

            curFreq[ch - 'a']++;
            if (curFreq[ch - 'a'] <= freq[ch - 'a']) {
                cnt++;
            }

            if (cnt == n) {
                char ch1 = str.charAt(start);
                while (start <= index && (freq[ch1 - 'a'] == 0 || curFreq[ch1 - 'a'] > freq[ch - 'a'])) {
                    if (curFreq[ch1 - 'a'] > freq[ch - 'a']) {
                        curFreq[ch1 - 'a']--;
                    }

                    start++;
                    ch1 = str.charAt(start);
                }

                if (res.isEmpty() || (index - start + 1) < res.length()) {
                    res = str.substring(start, index + 1);
                }

                cnt--;
                curFreq[ch1 - 'a']--;
                start++;
            }

            index++;
        }

        return res;
    }
}
