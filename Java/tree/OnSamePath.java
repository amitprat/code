package programs.tree;

import programs.types.TreeNode;

import java.util.Arrays;
import java.util.List;

public class OnSamePath {
    public static void test() {
        TreeNode<Integer> root = new TreeNode<>(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(2);
        root.left.left = new TreeNode(7);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(4);
        root.right.left.left = new TreeNode(6);
        root.right.left.right = new TreeNode(5);

        List<Integer> g = Arrays.asList(1, 2, 7);

        boolean res = isOnSamePath(root, g, 0);
        System.out.println(res);
    }

    private static boolean isOnSamePath(TreeNode<Integer> root, List<Integer> g, int idx) {
        if (idx == g.size()) return true;
        if (root == null || root.val != g.get(idx)) return false;

        if (isOnSamePath(root.left, g, idx + 1)) return true;
        return isOnSamePath(root.right, g, idx + 1);
    }
}
