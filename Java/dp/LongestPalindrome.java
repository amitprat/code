package programs.dp;

import programs.types.Pair;

public class LongestPalindrome {
    public static void test() {
        LongestPalindrome ob = new LongestPalindrome();
        String str = "abcdcba";
        System.out.println(ob.longestPalinOptimized(str));

        str = " hello . you uoy era woh..";
        System.out.println(ob.longestPalinOptimized(str));
    }

    private String longestPalin(String str) {
        Pair<Integer, Integer> range = null;
        for (int s = 0; s < str.length(); s++) {
            Pair<Integer, Integer> p = extend(s, s, str);
            if (compareTo(range, p)) {
                range = p;
            }
        }

        for (int s = 0; s < str.length() - 1; s++) {
            Pair<Integer, Integer> p = extend(s, s + 1, str);
            if (compareTo(range, p)) {
                range = p;
            }
        }

        return str.substring(range.first, range.second + 1);
    }

    private String longestPalinOptimized(String str) {
        Pair<Integer, Integer> range = null;
        for (int s = 0; s < str.length() - 1; s++) {
            Pair<Integer, Integer> p = extend(s, s, str);
            Pair<Integer, Integer> q = extend(s, s + 1, str);
            range = getMax(range, p, q);
        }

        return str.substring(range.first, range.second + 1);
    }

    private Pair<Integer, Integer> getMax(Pair<Integer, Integer> range, Pair<Integer, Integer> p, Pair<Integer, Integer> q) {
        int pdiff = p.second - p.first;
        int qdiff = q.second - q.first;
        if (pdiff < qdiff) {
            pdiff = qdiff;
            p = q;
        }
        if (range != null) {
            int rangeDiff = range.second - range.first;
            return pdiff > rangeDiff ? p : range;
        }
        return p;
    }

    private boolean compareTo(Pair<Integer, Integer> f, Pair<Integer, Integer> s) {
        if (f == null) return true;
        int curDiff = f.second - f.first;
        int newDiff = s.second - s.first;
        return newDiff > curDiff;
    }

    private Pair<Integer, Integer> extend(int i, int j, String str) {
        while (i >= 0 && j < str.length()) {
            if (str.charAt(i) != str.charAt(j)) break;
            i--;
            j++;
        }
        return new Pair<>(i + 1, j - 1);
    }
}
