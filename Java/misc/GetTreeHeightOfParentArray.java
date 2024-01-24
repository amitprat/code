package programs.misc;

public class GetTreeHeightOfParentArray {
    public static void test() {
        GetTreeHeightOfParentArray obj = new GetTreeHeightOfParentArray();
        int[] parents = {3, 3, 3, -1, 2};
        int height = obj.getTreeHeight(parents);
        System.out.println(height);
    }

    private int getTreeHeight(int[] parents) {
        int mxHeight = 0;
        int[] heights = new int[parents.length];
        for (int i = 0; i < parents.length; i++) heights[i] = -1;
        for (int i = 0; i < parents.length; i++) {
            mxHeight = Math.max(mxHeight, height(parents, i, heights));
        }
        return mxHeight;
    }

    private int height(int[] parents, int e, int[] heights) {
        if (e == -1) return 0;
        if (heights[e] != -1) return heights[e];
        heights[e] = 1 + height(parents, parents[e], heights);
        return heights[e];
    }
}
