package programs.tree;

import programs.types.TreeNode;

import java.util.*;

public class TreeReverseTraversal {
    public static void test() {
        TreeReverseTraversal obj = new TreeReverseTraversal();
        TreeNode<Integer> root = new TreeNode<>(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(7);

        System.out.println("Print in line: ");
        obj.reverseLevelOrder(root);

        System.out.println("Print in separate lines: ");
        obj.reverseLevelOrder1(root);
    }

    private void reverseLevelOrder(TreeNode<Integer> root) {
        Stack<TreeNode<Integer>> st = new Stack<>();
        Queue<TreeNode<Integer>> q = new LinkedList<>();

        q.add(root);
        while (!q.isEmpty()) {
            var cur = q.poll();
            st.push(cur);
            if (cur.right != null) q.add(cur.right);
            if (cur.left != null) q.add(cur.left);
        }

        while (!st.empty()) {
            System.out.print(st.pop().val + " ");
        }
        System.out.println();
    }

    private void reverseLevelOrder1(TreeNode<Integer> root) {
        Stack<List<TreeNode<Integer>>> st = new Stack<>();
        Queue<TreeNode<Integer>> q = new LinkedList<>();

        q.add(root);
        while (!q.isEmpty()) {
            int n = q.size();
            List<TreeNode<Integer>> l = new ArrayList<>();
            while (n-- > 0) {
                var cur = q.poll();
                l.add(cur);

                if (cur.left != null) q.add(cur.left);
                if (cur.right != null) q.add(cur.right);
            }
            st.push(l);
        }

        while (!st.empty()) {
            var cur = st.pop();
            for (var item : cur) System.out.print(item.val + " ");
            System.out.println();
        }
    }
}
