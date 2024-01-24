package programs.careercup;

import java.util.Arrays;

public class SwapCarsInCarParkingLot {
    public static void test() {
        int[] originalOrder = {4, 6, 5, 1, 7, 3, 2, 0};
        int[] arr = {0, 1, 2, 3, 7, 6, 4, 5};

        correctOrder(arr, originalOrder);
        System.out.println(Arrays.toString(arr));
    }

    private static void correctOrder(int[] pos, int[] originalOrder) {
        int[] correctPos = new int[originalOrder.length];
        int emptyPos = -1;
        for (int i = 0; i < originalOrder.length; i++) {
            correctPos[originalOrder[i]] = i;
            if (pos[i] == 0) emptyPos = i;
        }

        for (int i = 0; i < pos.length; ) {
            if (i != correctPos[pos[i]]) {
                emptyPos = swap(pos, i, correctPos[pos[i]], emptyPos);
            } else
                i++;
        }
    }

    private static int swap(int[] pos, int old, int newPos, int empty) {
        if (old == empty || newPos == empty) {
            if (old == empty) {
                pos[old] = pos[newPos];
                pos[newPos] = 0;
                return newPos;
            } else {
                pos[newPos] = pos[old];
                pos[old] = 0;
                return old;
            }
        }

        pos[empty] = pos[newPos];
        pos[newPos] = pos[old];
        pos[old] = pos[empty];

        return empty;
    }
}
