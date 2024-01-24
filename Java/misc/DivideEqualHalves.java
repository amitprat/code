package programs.misc;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class DivideEqualHalves {
    public static void test() {
        List<Integer> arr = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8,9,10,100,90);
        int sum = arr.stream().mapToInt(Integer::intValue).sum();

        Set<Integer> otherHalf = new HashSet<>();
        var res = findSubset(arr, arr.size(), arr.size() / 2, sum / 2, otherHalf);

        if (res) {
            String first = "";
            String second = "";
            for (int i = 0; i < arr.size(); i++) {
                if (!otherHalf.contains(i)) first += arr.get(i).toString() + " ";
                else second += arr.get(i).toString() + " ";
            }

            System.out.println(first);
            System.out.println(second);
        }
    }

    private static boolean findSubset(List<Integer> arr, int n, int cnt, int sum, Set<Integer> otherHalf) {
        if (sum == 0 && cnt == 0) return true;
        if (cnt <= 0 || n <= 0) return false;

        otherHalf.add(n - 1);
        var incl = findSubset(arr, n - 1, cnt - 1, sum - arr.get(n - 1), otherHalf);
        if (incl) return true;
        otherHalf.remove(n - 1);

        return findSubset(arr, n - 1, cnt, sum, otherHalf);
    }
}
