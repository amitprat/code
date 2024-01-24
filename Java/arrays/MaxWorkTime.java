package programs.arrays;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class MaxWorkTime {
    public static void test() {
        MaxWorkTime obj = new MaxWorkTime();
        {
            int n = 5;
            Node[] arr = new Node[n];
            arr[0] = obj.new Node(600, 930, 330);
            arr[1] = obj.new Node(900, 1230, 330);
            arr[2] = obj.new Node(1200, 1430, 230);
            arr[3] = obj.new Node(1000, 1030, 30);
            arr[4] = obj.new Node(1100, 1330, 230);

            obj.printMaxWorkTime(arr);
        }

        System.out.println("\n\n");

        {
            int n = 6;
            Node[] arr = new Node[n];
            arr[0] = obj.new Node(600, 830, 230);
            arr[1] = obj.new Node(900, 1100, 200);
            arr[2] = obj.new Node(1230, 1400, 130);
            arr[3] = obj.new Node(800, 900, 100);
            arr[4] = obj.new Node(1030, 1400, 330);
            arr[5] = obj.new Node(900, 1130, 230);

            obj.printMaxWorkTime(arr);
        }
    }

    private void printMaxWorkTime(Node[] arr) {
        Arrays.sort(arr);
        int[] dp = new int[arr.length];
        for (int i = 0; i < arr.length; i++) dp[i] = arr[i].diff;
        int mx = 0;
        for (int i = 1; i < arr.length; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (arr[i].start >= arr[j].end) {
                    dp[i] = Math.max(dp[i], dp[j] + arr[i].diff);
                    mx = Math.max(mx, dp[i]);
                }
            }
        }

        System.out.println(mx);
    }

    private class Node implements Comparable {
        int start;
        int end;
        int diff;

        Node(int start, int end, int diff) {
            this.start = start;
            this.end = end;
            this.diff = diff;
        }

        @Override
        public int compareTo(@NotNull Object o) {
            return end - ((Node) o).end;
        }
    }
}
