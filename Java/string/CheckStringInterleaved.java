package programs.string;

public class CheckStringInterleaved {
    public static void test() {
        CheckStringInterleaved obj = new CheckStringInterleaved();

        {
            String a = "abcd";
            String b = "xyz";
            String c = "axybczd";

            System.out.println(obj.isInterLeaved(a, b, c));
        }

        {
            String a = "xbcd";
            String b = "azy";
            String c = "axybczd";

            System.out.println(obj.isInterLeaved(a, b, c));
        }
    }

    private boolean isInterLeaved(String a, String b, String c) {
        int i = a.length() - 1;
        int j = b.length() - 1;
        int k = c.length() - 1;

        while (k >= 0) {
            if (i >= 0 && c.charAt(k) == a.charAt(i)) i--;
            else if (j >= 0 && c.charAt(k) == b.charAt(j)) j--;
            else break;
            k--;
        }

        return i == -1 && j == -1 && k == -1;
    }
}
