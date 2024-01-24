#include "../header.h"

/*
https://careercup.com/question?id=83756

Write a progam to rotate a matrix by 90 degrees.

private static int[][] rotateMatrixBy90Degree(int[][] matrix, int n) {
    for (int layer = 0; layer < n / 2; layer++) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int top = matrix[first][i];
            matrix[first][i] = matrix[last - offset][first];
            matrix[last - offset][first] = matrix[last][last - offset];
            matrix[last - offset][last] = matrix[i][last];
            matrix[i][last] = top;
        }
    }
    System.out.println("Matrix After Rotating 90 degree:-");
    printMatrix(matrix, n);
    return matrix;
}
*/
class RotateMatrixBy90Degree {
};