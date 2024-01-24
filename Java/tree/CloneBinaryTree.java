package Java.tree;

import java.util.HashMap;
import java.util.Map;

public class CloneBinaryTree {
    public static void test() {
        CloneBinaryTree obj = new CloneBinaryTree();
        Node root = obj.construct();

        System.out.print("Old Tree: ");
        obj.inorder(root);
        System.out.println();

        System.out.print("New Tree: ");
        Node newRoot = obj.clone(root);
        obj.inorder(newRoot);
        System.out.println();
    }

    public Node clone(Node cur) {
        Map<Node, Node> nodeMap = new HashMap<>();
        Node newRoot = copyNodes(cur, nodeMap);
        copyRandomPtr(cur, newRoot, nodeMap);

        return newRoot;
    }

    private Node copyNodes(Node cur, Map<Node, Node> nodeMap) {
        if (cur == null)
            return cur;

        Node newNode = new Node(cur.val);
        nodeMap.put(cur, newNode);

        newNode.left = copyNodes(cur.left, nodeMap);
        newNode.right = copyNodes(cur.right, nodeMap);

        return newNode;
    }

    private void copyRandomPtr(Node oldNode, Node newNode, Map<Node, Node> nodeMap) {
        if (oldNode == null)
            return;

        newNode.random = nodeMap.getOrDefault(oldNode.random, null);

        copyRandomPtr(oldNode.left, newNode.left, nodeMap);
        copyRandomPtr(oldNode.right, newNode.right, nodeMap);
    }

    private void inorder(Node cur) {
        if (cur != null) {
            inorder(cur.left);
            System.out.print(cur + ", ");
            inorder(cur.right);
        }
    }

    private Node construct() {
        Node root = null;
        root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        root.left.left = new Node(4);
        root.left.right = new Node(5);
        root.random = root.left.right;
        root.left.left.random = root;
        root.left.right.random = root.right;

        return root;
    }

    class Node {
        int val;
        Node left, right, random;

        Node(int val) {
            this.val = val;
            this.left = this.right = this.random = null;
        }

        @Override
        public String toString() {
            String str = "(val:";
            str += Integer.toString(val);
            if (left != null)
                str += ",left:" + left.val;
            if (right != null)
                str += ",right:" + right.val;
            if (random != null)
                str += ",random:" + random.val;
            str += ")";

            return str;
        }
    }
}
