package programs.careercup;

import java.util.ArrayList;
import java.util.Arrays;

public class GenerateOriginalArrayFromHeightArray {
    public static void test() {
        int[] heights = {6, 3, 0, 2, 2, 0, 0};//  6 7
        var res = generateOriginalArray(heights);
        System.out.println(Arrays.toString(res));

        System.out.println(generate(heights));
    }

    private static int[] generateOriginalArray(int[] heights) {
        ArrayList<Integer> remain = new ArrayList<>();
        for (int i = 0; i < heights.length; i++) {
            remain.add(heights.length - i);
        }
        System.out.println(remain);
        int[] newArr = new int[heights.length];
        for (int i = 0; i < heights.length; i++) {
            newArr[i] = remain.get(heights[i]);
            remain.remove(heights[i]);
        }

        return newArr;
    }

    public static String generate(int[] input) {
        String result = "";
        ArrayList<Integer> remain = new ArrayList<Integer>();
        for (int i = 0; i < input.length; i++) {
            remain.add(input.length - i);
        }
        for (int i = 0; i < input.length; i++) {
            result = result + " " + remain.get(input[i]);
            remain.remove(input[i]);
        }
        return result;
    }
}
