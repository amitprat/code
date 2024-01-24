package programs.tree;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class MergeBSTs {
    public static void test() {
        MergeBSTs obj = new MergeBSTs();
        Node<Integer> root1 = new Node(3);
        root1.left = new Node(1);
        root1.right = new Node(5);
        root1.right.left = new Node(4);
        root1.right.right = new Node(6);
        obj.inorder(root1);
        System.out.println();

        Node<Integer> root2 = new Node(10);
        root2.left = new Node(5);
        root2.right = new Node(15);
        root2.left.left = new Node(2);
        root2.left.right = new Node(7);
        obj.inorder(root2);
        System.out.println();

        List<Node<Integer>> root = obj.mergeBST1(root1, root2);
        System.out.println(root);
    }

    public void inorder(Node<Integer> root) {
        if (root != null) {
            inorder(root.left);
            System.out.print(root + " ");
            inorder(root.right);
        }
    }

    public List<Node<Integer>> mergeBST(Node<Integer> root1, Node<Integer> root2) {
        Stack<Node<Integer>> st1 = new Stack<>();
        Stack<Node<Integer>> st2 = new Stack<>();

        st1.push(root1);
        st2.push(root2);

        List<Node<Integer>> root = new ArrayList<>();
        boolean process1 = true, process2 = true;

        while (true) {
            if (process1 && !st1.empty()) {
                var top1 = st1.pop();
                while (top1 != null) {
                    st1.push(top1);
                    top1 = top1.left;
                }
                process1 = false;
            }

            if (process2 && !st2.empty()) {
                var top2 = st2.pop();
                while (top2 != null) {
                    st2.push(top2);
                    top2 = top2.left;
                }
                process2 = false;
            }
            if (st1.empty() && st2.empty()) break;

            if (st2.empty() || (!st1.empty() && st1.peek().val <= st2.peek().val)) {
                var tmp = st1.pop();
                root.add(tmp);
                st1.push(tmp.right);
                process1 = true;
            } else {
                var tmp = st2.pop();
                root.add(tmp);
                st2.push(tmp.right);
                process2 = true;
            }
        }

        return root;
    }

    public List<Node<Integer>> mergeBST1(Node<Integer> root1, Node<Integer> root2) {
        Stack<Node<Integer>> st1 = new Stack<>();
        Stack<Node<Integer>> st2 = new Stack<>();

        List<Node<Integer>> root = new ArrayList<>();
        boolean process1 = true, process2 = true;

        while (true) {
            while (root1 != null) {
                st1.push(root1);
                root1 = root1.left;
            }

            while (root2 != null) {
                st2.push(root2);
                root2 = root2.left;
            }
            if (st1.empty() && st2.empty()) break;

            if (st2.empty() || (!st1.empty() && st1.peek().val <= st2.peek().val)) {
                root.add(st1.peek());
                root1 = st1.pop().right;
            } else {
                root.add(st2.peek());
                root2 = st2.pop().right;
            }
        }

        return root;
    }
}
