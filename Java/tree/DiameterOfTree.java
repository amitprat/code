package Java.tree;

import Java.types.Pair;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class DiameterOfTree {
    public static void test() {
        DiameterOfTree obj = new DiameterOfTree();
        Tree<Integer> tree = obj.new Tree<>();
        tree.add(3);
        tree.add(1);
        tree.add(4);
        tree.add(2);
        tree.add(5);

        System.out.println("Inorder: ");
        tree.inorder();
        System.out.println("\n");

        System.out.println("Level order: ");
        tree.levelOrder();
        System.out.println();

        System.out.println("Diameter of tree = " + tree.diameter());
    }

    class Tree<T extends Comparable<T>> {
        Node root = null;

        public void add(T val) {
            root = add(root, val);
        }

        private Node add(Node cur, T val) {
            if (cur == null)
                return new Node(val);

            if (val.compareTo(cur.val) < 0)
                cur.left = add(cur.left, val);
            else
                cur.right = add(cur.right, val);

            return cur;
        }

        public void levelOrder() {
            Queue<Node> q = new LinkedList<>();
            q.add(root);
            while (!q.isEmpty()) {
                int n = q.size();
                while (n-- != 0) {
                    var front = q.poll();
                    System.out.print(front + " ");

                    if (front.left != null)
                        q.add(front.left);
                    if (front.right != null)
                        q.add(front.right);
                }
                System.out.println();
            }
        }

        public Pair<Integer, Integer> diameter() {
            return diameter(root);
        }

        private Pair<Integer, Integer> diameter(Node cur) {
            if (cur == null)
                return new Pair<>(0, 0);

            var ld = diameter(cur.left);
            var rd = diameter(cur.right);

            int h = Math.max(ld.second, rd.second) + 1;
            int r = Math.max(h, Math.max(ld.first, rd.first));

            return new Pair<>(r, h);
        }

        public void inorder() {
            Stack<Node> st = new Stack<>();
            st.push(root);

            while (!st.empty()) {
                var top = st.pop();
                while (top != null) {
                    st.push(top);
                    top = top.left;
                }
                if (st.empty())
                    break;
                top = st.pop();
                System.out.print(top + " ");
                st.push(top.right);
            }
        }

        public int height(Node cur) {
            if (cur == null)
                return 0;

            return 1 + Math.max(height(cur.left), height(cur.right));
        }

        class Node {
            T val;
            Node left, right;

            Node(T val) {
                this.val = val;
                this.left = null;
                this.right = null;
            }

            @Override
            public String toString() {
                return val.toString();
            }
        }
    }
}
