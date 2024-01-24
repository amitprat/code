package programs.matrix;

public class PrintDiagonal {
    public static void test() {
        PrintDiagonal obj = new PrintDiagonal();
        int n = 3;
        int m = 4;
        int[][] arr = new int[n][m];
        arr[0] = new int[]{1, 2, 3, 4};
        arr[1] = new int[]{5, 6, 7, 8};
        arr[2] = new int[]{9, 10, 11, 12};

        obj.printDiag(arr);
    }

    private void printDiag(int[][] arr) {
        for (int row = arr.length - 1, col = 0; col < arr[0].length; ) {
            printCurrentDiag(arr, row, col);
            System.out.println();
            if (row > 0) row--;
            else col++;
        }
    }

    private void printCurrentDiag(int[][] arr, int row, int col) {
        for (int i = 0, j = 0; row + i < arr.length && col + j < arr[i].length; i++, j++) {
            System.out.print(arr[row + i][col + j] + " ");
        }
    }
}
