package programs.careercup;

import programs.types.TreeNode;

import java.util.Arrays;

public class FindNextLeastGreaterElement {
    public static void test() {
        FindNextLeastGreaterElement obj = new FindNextLeastGreaterElement();
        int[] arr = {8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28};

        var res = obj.getNextGreater(arr);
        System.out.println(Arrays.toString(arr));
        System.out.println(Arrays.toString(res));
    }

    private int[] getNextGreater(int[] arr) {
        int[] res = new int[arr.length];
        TreeNode<Integer> root = null;
        for (int i = arr.length - 1; i >= 0; i--) {
            root = insert(root, arr[i]);
            res[i] = successor(root, arr[i]);
        }

        return res;
    }

    private int successor(TreeNode<Integer> root, Integer val) {
        if (root == null) return -1;
        if (root.val < val) {
            return successor(root.right, val);
        } else if (root.val > val) {
            int cur = successor(root.left, val);
            return cur == -1 ? root.val : cur;
        } else {
            if (root.right != null) {
                TreeNode<Integer> cur = root.right;
                while (cur.left != null) {
                    cur = cur.left;
                }
                return cur.val;
            }
        }
        return -1;
    }

    private TreeNode<Integer> insert(TreeNode<Integer> root, int element) {
        if (root == null) return new TreeNode<>(element);
        if (element < root.val) root.left = insert(root.left, element);
        else if (element > root.val) root.right = insert(root.right, element);
        else root.val = element;

        return root;
    }
}
