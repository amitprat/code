package programs.careercup;

import programs.types.Point;

public class LargestSubsquareSurroundedBy1s {
    public static void test() {
        LargestSubsquareSurroundedBy1s obj = new LargestSubsquareSurroundedBy1s();
        {
            int[][] mat = new int[][]{
                    {0, 1, 0, 0, 1},
                    {1, 0, 1, 0, 1},
                    {0, 1, 1, 1, 0},
                    {0, 1, 0, 1, 1},
                    {1, 1, 1, 1, 0}
            };

            var res = obj.largestArea(mat);

            System.out.printf("Largest Square = %d", res);
            System.out.println();
        }

        {
            int[][] mat = new int[][]{
                    {1, 1, 1, 1, 1, 1},
                    {1, 0, 1, 1, 0, 1},
                    {0, 1, 1, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 1, 0, 1},
                    {1, 0, 1, 1, 0, 0},
                    {1, 0, 1, 0, 1, 1},
                    {1, 1, 1, 0, 1, 1}
            };
            var res = obj.largestArea(mat);
            System.out.printf("The size of largest square sub-matrix is %d", res);
            System.out.println();
        }
    }

    private int largestArea(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;
        Point[][] memo = new Point[n][m]; // 0 initialized
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                memo[i][j] = new Point(0, 0);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 1) {
                    if (i == 0 && j == 0) memo[i][j] = new Point(1, 1);
                    else if (i == 0) memo[i][j] = new Point(memo[i][j - 1].x + 1, 1);
                    else if (j == 0) memo[i][j] = new Point(1, memo[i - 1][j].y + 1);
                    else memo[i][j] = new Point(memo[i][j - 1].x + 1, memo[i - 1][j].y + 1);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(memo[i][j] + "\t");
            }
            System.out.println();
        }

        int mxArea = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (mat[i][j] == 1) {
                    int curLen = Math.min(memo[i][j].x, memo[i][j].y);
                    while (curLen != 0) {
                        boolean isSquare = memo[i - curLen + 1][j].x >= curLen &&
                                memo[i][j - curLen + 1].y >= curLen;

                        if (isSquare) {
                            mxArea = Math.max(mxArea, curLen);
                            break;
                        }
                        curLen--;
                    }
                }
            }
        }

        return mxArea;
    }
}
