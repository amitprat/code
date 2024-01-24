package Java.tree;
import java.util.Stack;

public class MergeBST {
    private Node head = null;

    static void test() {
        MergeBST obj = new MergeBST();

        Node tree1 = obj.new Node(3);
        tree1.left = obj.new Node(1);
        tree1.right = obj.new Node(5);

        Node tree2 = obj.new Node(4);
        tree2.left = obj.new Node(2);
        tree2.right = obj.new Node(6);

        obj.print(tree1);
        System.out.println();

        obj.print(tree2);
        System.out.println();
        
        Node root = obj.mergeTrees(tree1, tree2);
        
        obj.print(root);
        System.out.println();
    }

    public Node mergeTrees(Node tree1, Node tree2) {
        Node root = merge(tree1, tree2);
        int n = 0;
        Node tmp = root;
        while (tmp != null) {
            tmp = tmp.right;
            n++;
        }
        head = root;
        root = createBalanceBst(n);

        return root;
    }

    public Node createBalanceBst(int n) {
        if (n <= 0) return null;
        
        Node left = createBalanceBst(n / 2);
        Node root = head;
        root.left = left;
        head = head.right;
        root.right = createBalanceBst(n - n / 2 - 1);

        return root;
    }

    private Node merge(Node tree1, Node tree2) {
        Node root = null;
        Node cur = null;

        Stack<Node> stack1 = new Stack<>();
        Stack<Node> stack2 = new Stack<>();
        boolean done = false;
        boolean process1 = true;
        boolean process2 = true;

        while (!done) {
            if (process1) {
                while (tree1 != null) {
                    stack1.push(tree1);
                    tree1 = tree1.left;
                }
                if (!stack1.empty()) tree1 = stack1.pop();
                process1 = false;
            }

            if (process2) {
                while (tree2 != null) {
                    stack2.push(tree2);
                    tree2 = tree2.left;
                }
                if (!stack2.empty()) tree2 = stack2.pop();
                process2 = false;
            }
            if (tree1 == null && tree2 == null) {
                done = true;
                continue;
            }

            if (tree1 == null || tree2.val < tree1.val) {
                Node next2 = tree2.right;
                if (root == null) root = cur = tree2;
                else {
                    cur.right = tree2;
                    tree2.left = cur;
                }
                cur = tree2;
                tree2 = next2;
                process2 = true;
            } else if (tree2 == null || tree1.val < tree2.val) {
                Node next1 = tree1.right;
                if (root == null) root = cur = tree1;
                else {
                    cur.right = tree1;
                    tree1.left = cur;
                }
                cur = tree1;
                tree1 = next1;
                process1 = true;
            }
        }

        return root;
    }

    public void inorder(Node tree1) {
        if (tree1 != null) {
            inorder(tree1.left);
            System.out.print(tree1.val + " ");
            inorder(tree1.right);
        }
    }

    private class Node {
        int val;
        Node left, right;

        Node(int val) {
            this.val = val;
            this.left = null;
            this.right = null;
        }
    }
}
