package programs.dp;

public class LongestPalinSubseq {
    public static void test() {
        LongestPalinSubseq obj = new LongestPalinSubseq();
        String str = "GEEKS FOR GEEKS";
        System.out.println(obj.longestPalinRec(str));
        System.out.println(obj.longestPalinDP(str));
        System.out.println(obj.longestPalinSubstr(str));
    }

    public int longestPalinDP(String str) {
        int n = str.length();
        int[][] table = new int[n][n];
        for (int i = 0; i < n; i++) {
            table[i][i] = 1;
        }
        for (int cl = 2; cl <= n; cl++) {
            for (int s = 0; s < n - cl + 1; s++) {
                int e = s + cl - 1;
                if (str.charAt(s) == str.charAt(e) && cl == 2)
                    table[s][e] = 2;
                else if (str.charAt(s) == str.charAt(e))
                    table[s][e] = table[s + 1][e - 1] + 2;
                else table[s][e] = Math.max(table[s][e - 1], table[s + 1][e]);
            }
        }
        return table[0][n - 1];
    }

    public int longestPalinRec(String str) {
        return longestPalinRec(str, 0, str.length() - 1);
    }

    private int longestPalinRec(String str, int s, int e) {
        if (s == e) return 1;
        if (s + 1 == e) return str.charAt(s) == str.charAt(e) ? 2 : 1;
        if (str.charAt(s) == str.charAt(e)) return 2 + longestPalinRec(str, s + 1, e - 1);
        return Math.max(longestPalinRec(str, s + 1, e), longestPalinRec(str, s, e - 1));
    }

    private int longestPalinSubstr(String str) {
        int mxLen = 1;
        int n = str.length();
        for (int i = 1; i < n; i++) {
            int s = i - 1;
            int e = i;
            while (s >= 0 && e < n && str.charAt(s) == str.charAt(e)) {
                if (e - s + 1 > mxLen) mxLen = e - s + 1;
                s--;
                e++;
            }

            s = i - 1;
            e = i + 1;
            while (s >= 0 && e < n && str.charAt(s) == str.charAt(e)) {
                if (e - s + 1 > mxLen) mxLen = e - s + 1;
                s--;
                e++;
            }
        }
        return mxLen;
    }
}
