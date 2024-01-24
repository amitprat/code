package programs.careercup;

import java.util.Arrays;
import java.util.stream.Collectors;

public class SetRowColsToZeros {
    public static void test() {
        int[][] matrix = {
                {1, 0, 0, 1, 1, 1},
                {1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1},
                {0, 1, 1, 1, 1, 0},
                {1, 1, 1, 1, 1, 1}
        };

        setZeros(matrix);
        System.out.println(Arrays.stream(matrix).map(Arrays::toString)
                .collect(Collectors.joining(System.lineSeparator())));
    }

    private static void setZeros(int[][] matrix) {
        if (matrix.length == 0) return;
        int n = matrix.length;
        int m = matrix[0].length;
        boolean isFirstRowZero = false, isFirstColZero = false;
        for (int i = 0; i < m; i++) {
            if (matrix[0][i] == 0) {
                isFirstRowZero = true;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) {
                isFirstColZero = true;
                break;
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (isFirstColZero) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
            }
        }

        if (isFirstRowZero) {
            for (int i = 0; i < m; i++) {
                matrix[0][i] = 0;
            }
        }
    }
}
