package programs.maths;

import java.util.Arrays;
import java.util.List;

public class IsAggregateNumber {
    public static void test() {
        List<String> strs = Arrays.asList("123", "312", "112358", "122436", "1299111210", "112112224", "0132");
        IsAggregateNumber obj = new IsAggregateNumber();

        for (var str : strs) {
            System.out.printf("Is Aggregate (%s) = %b\n", str, obj.isAggregate(str));
        }
    }

    private boolean isAggregate(String str) {
        for (int i = 1; i <= str.length() - 2; i++) {
            for (int j = i; j + i <= str.length() - 1; j += i) {
                if (isMatch(str, i, j)) return true;
            }
        }
        return false;
    }

    private boolean isMatch(String str, int l1, int l2) {
        int total = str.length();
        StringBuffer sb = new StringBuffer();
        int a = Integer.parseInt(str.substring(0, l1));
        int b = Integer.parseInt(str.substring(l1, l1 + l2));
        sb.append(a);
        sb.append(b);
        int l = l1 + l2;
        while (l < total) {
            int c = a + b;
            sb.append(c);
            a = b;
            b = c;
            l += String.valueOf(c).length();
        }

        var res = l == total && sb.toString().equals(str);
        if (res) {
            System.out.printf("Found aggr for %s with a=%s,b=%s,complete=%s\n",
                    str, str.substring(0, l1), str.substring(l1, l1 + l2), sb);
        }

        return res;
    }
}
