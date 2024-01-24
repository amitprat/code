package programs.matrix;

public class FindWordSequence {
    public static void test() {
        char[][] arr = {
                {'a', 'b', 'c', 'd', 'e'},
                {'f', 'g', 'h', 'i', 'j'},
                {'k', 'l', 'm', 'n', 'o'},
                {'p', 'q', 'r', 's', 't'},
                {'u', 'v', 'w', 'x', 'y'},
                {'z', '\0', '\0', '\0', '\0'}
        };

        String word = "aston";

        printSeq(arr, word);
    }

    private static void printSeq(char[][] arr, String word) {
        int curx = 0, cury = 0;
        StringBuilder sb = new StringBuilder();
        for (Character ch : word.toCharArray()) {
            int desx = (ch - 'a') / 5;
            int desy = (ch - 'a') % 5;

            char dir = '!';
            int mv = 0;

            if (desx > curx) {
                dir = 'd';
                mv = 1;
            } else {
                dir = 'u';
                mv = -1;
            }

            while (curx != desx) {
                sb.append(dir);
                curx += mv;
            }

            if (desy > cury) {
                dir = 'r';
                mv = 1;
            } else {
                dir = 'l';
                mv = -1;
            }

            while (cury != desy) {
                sb.append(dir);
                cury += mv;
            }

            sb.append('!');
        }

        System.out.println(sb);
    }
}
