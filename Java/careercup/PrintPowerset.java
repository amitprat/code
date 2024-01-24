package programs.careercup;

import java.util.*;

public class PrintPowerset {
    public static void test() {
        PrintPowerset obj = new PrintPowerset();
        int[] set = {1, 3, 1};

        obj.printIterative(set);

        obj.printRecursive(set);

        obj.printRecursiveDistinct(set);

        obj.printIterativeDistinct(set);
    }

    private void printIterativeDistinct(int[] set) {
        System.out.println("Print iterative: ");
        int m = set.length;
        int n = 1 << m;
        Arrays.sort(set);
        Set<String> response = new HashSet<>();

        for (int i = 0; i < n; i++) {
            String subset = "";
            for (int j = 0; j < m; j++) {
                if ((i & (1 << j)) != 0) {
                    subset += set[j] + " ";
                }
            }
            response.add(subset);
        }

        System.out.println(response);
    }

    private void printRecursiveDistinct(int[] set) {
        System.out.println("Print distinct iterative: ");
        Arrays.sort(set);
        List<Integer> result = new ArrayList<>();
        printRecursiveDistinct(set, 0, result);
    }

    private void printRecursiveDistinct(int[] set, int index, List<Integer> result) {
        if (index == set.length) {
            System.out.println(result);
            return;
        }

        result.add(set[index]);
        printRecursiveDistinct(set, index + 1, result);
        result.remove(result.size() - 1);

        while (index + 1 < set.length && set[index + 1] == set[index]) index++;
        printRecursiveDistinct(set, index + 1, result);
    }

    private void printRecursive(int[] set) {
        System.out.println("Recursive subset: ");
        List<Integer> cur = new ArrayList<>();
        printRecursive(set, 0, cur);
    }

    private void printRecursive(int[] set, int index, List<Integer> curRes) {
        if (index == set.length) {
            System.out.println(curRes);
            return;
        }

        printRecursive(set, index + 1, curRes);
        curRes.add(set[index]);
        printRecursive(set, index + 1, curRes);
        curRes.remove(curRes.size() - 1);
    }

    private void printIterative(int[] set) {
        System.out.println("Iterative subset: ");
        int n = 1 << set.length;
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            List<Integer> cur = new ArrayList<>();
            for (int j = 0; j < set.length; j++) {
                if ((i & (1 << j)) != 0) {
                    cur.add(set[j]);
                }
            }
            result.add(cur);
        }

        System.out.println(result);
    }
}
