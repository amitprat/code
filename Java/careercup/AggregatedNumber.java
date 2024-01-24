package programs.careercup;

import java.util.ArrayList;
import java.util.List;

/*
https://www.careercup.com/question?id=14948278

we will name a number "aggregated number" if this number has the following attribute:
just like the Fibonacci numbers
1,1,2,3,5,8,13.....

the digits in the number can divided into several parts, and the later part is the sum of the former parts.

like 112358, because 1+1=2, 1+2=3, 2+3=5, 3+5=8
122436, because 12+24=36
1299111210, because 12+99=111, 99+111=210
112112224, because 112+112=224
so can you provide a function to check whether this number is aggregated number or not?
 */

public class AggregatedNumber {
    public static void test() {
        AggregatedNumber obj = new AggregatedNumber();
        List<String> nums = new ArrayList<>();
        nums.add("11");
        nums.add("112");
        nums.add("112358");
        nums.add("122436");
        nums.add("1299111210");
        nums.add("112112224");
        nums.add("1234578");

        for(var num : nums) {
            boolean res = obj.isAggregated(num);
            System.out.println(String.format("Is number %s is aggregated %s", num, res));
        }
    }

    public boolean isAggregated(String num) {
        for(int l1=1;l1<=num.length()/2;l1++) {
            for(int l2=l1+1;l2<=num.length();l2++) {
                if(l2 < num.length() && isMatch(num, l1, l2)) return true;
            }
        }

        return false;
    }

    private boolean isMatch(String num, int l1, int l2) {
        String first = num.substring(0, l1);
        String second = num.substring(l1, l2);

        while(l2 < num.length()) {
            String sum = String.valueOf(Integer.parseInt(first) + Integer.parseInt(second));
            if(l2+sum.length() > num.length()) return false;

            var next = num.substring(l2, l2+sum.length());
            if(Integer.parseInt(sum) != Integer.parseInt(next)) return false;

            first = second;
            second = next;
            l2 = l2 + sum.length();
        }

        return true;
    }
}
