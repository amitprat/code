package programs.matrix;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class FillMatrixWithWords {
    private final int N = 3;

    static void test() {
        FillMatrixWithWords obj = new FillMatrixWithWords();
        List<String> matrix = new ArrayList<>();
        Set<String> set = new HashSet<>();
        set.add("GET");
        set.add("OET");
        set.add("TET");
        set.add("GOT");
        set.add("EEE");
        set.add("TTT");

        boolean result = obj.fillMatrix(matrix, set);
        System.out.println("Result: " + result);
    }

    private boolean fillMatrix(List<String> matrix, Set<String> set) {
        for (String word : set) {
            matrix.add(word);
            if (fillColumns(matrix, set, 1)) return true;
        }

        return false;
    }

    private boolean fillColumns(List<String> matrix, Set<String> set, int row) {
        if (row == N) return true;
        List<String> prefixes = new ArrayList<>();
        for (int j = 0; j < N; j++) {
            StringBuilder cur = new StringBuilder();
            for (int i = 0; i < row; i++) {
                cur.append(matrix.get(i).charAt(j));
            }
            prefixes.add(cur.toString());
        }

        for (int j = 0; j < N; j++) {
            List<String> words = getMatchingWords(set, prefixes.get(j));
            StringBuilder next = new StringBuilder();
            for (String word : words) {
                next.append(word.charAt(0));
            }
            matrix.add(row, next.toString());
        }
        return fillColumns(matrix, set, row + 1);
    }

    List<String> getMatchingWords(Set<String> set, String prefix) {
        List<String> words = new ArrayList<>();
        for (String s : set) {
            if (s.startsWith(prefix)) words.add(s);
        }

        return words;
    }
}
