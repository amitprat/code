package programs.careercup;

import programs.types.Point;

public class SetupBox {
    public static void test() {
        char[][] arr = {
                {'a', 'b', 'c', 'd', 'e',},
                {'f', 'g', 'h', 'i', 'j',},
                {'k', 'l', 'm', 'n', 'o'},
                {'p', 'q', 'r', 's', 't'},
                {'u', 'v', 'w', 'x', 'y'},
                {'z'}
        };
        String word = "con";

        Point start = new Point(0, 0);
        printPath(arr, start, word);
    }

    private static void printPath(char[][] arr, Point start, String word) {
        for (char ch : word.toCharArray()) {
            Point dst = getPos(arr, ch);
            move(arr, start, dst);
        }
    }

    private static void move(char[][] arr, Point start, Point dst) {
        while (start.x != dst.x || start.y != dst.y) {
            while (dst.x < start.x && start.x >= 0 && start.y < arr[start.x - 1].length) {
                start.x--;
                System.out.print("UP ");
            }
            while (dst.x > start.x && start.x < arr.length && start.y < arr[start.x + 1].length) {
                start.x++;
                System.out.print("DOWN ");
            }
            while (dst.y < start.y && start.y >= 0) {
                start.y--;
                System.out.print("LEFT ");
            }
            while (dst.y > start.y && start.y < arr[start.x].length) {
                start.y++;
                System.out.print("RIGHT ");
            }
        }
        System.out.print("OK ");
    }

    private static Point getPos(char[][] arr, char ch) {
        int p = ch - 'a';
        return new Point(p / 5, p % 5);
    }
}
