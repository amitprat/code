package programs.string;

public class RemoveRepeatedCharsToMakeSmallestString {
    public static void test() {
        RemoveRepeatedCharsToMakeSmallestString obj = new RemoveRepeatedCharsToMakeSmallestString();
        String str = "bcabc";
        var res = obj.removeRepeated(str);
        System.out.println(str + " => " + res);

        str = "cbacdcbc";
        res = obj.removeRepeated(str);
        System.out.println(str + " => " + res);
    }

    private String removeRepeated(String str) {
        int n = str.length();
        int[] next = new int[n];
        int[] lastIndex = new int[26];
        boolean[] visited = new boolean[26];

        for (int i = 0; i < 26; i++) {
            lastIndex[i] = -1;
            visited[i] = false;
        }
        for (int i = n - 1; i >= 0; i--) {
            int p = str.charAt(i) - 'a';
            next[i] = lastIndex[p];
            lastIndex[p] = i;
        }

        StringBuffer ans = new StringBuffer();
        for (int i = 0; i < n; i++) {
            int p = str.charAt(i) - 'a';
            if (visited[p]) continue;
            if (next[i] == -1) {
                ans.append(str.charAt(i));
                visited[p] = true;
            } else {
                char smaller = str.charAt(i);
                for (int j = i + 1; j < n; j++) {
                    if (str.charAt(j) < smaller) smaller = str.charAt(j);
                    if (next[j] == -1) break;
                }
                if (str.charAt(i) <= smaller) {
                    ans.append(str.charAt(i));
                    visited[p] = true;
                }
            }
        }
        return ans.toString();
    }
}
