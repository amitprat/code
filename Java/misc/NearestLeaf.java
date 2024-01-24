package programs.misc;

import programs.types.TreeNode;

public class NearestLeaf {
    public static void test() {
        TreeNode<Integer> node = new TreeNode<Integer>(1);
        node.left = new TreeNode(2);
        node.right = new TreeNode(3);
        node.left.left = new TreeNode(4);
        node.right.right = new TreeNode(5);


    }
}
