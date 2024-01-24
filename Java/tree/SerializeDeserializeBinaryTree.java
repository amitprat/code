package programs.tree;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Stack;

public class SerializeDeserializeBinaryTree {
    public static void test() {
        // normal tree
        Tree<Integer> tree = new Tree<>();
        tree.root = new Tree.Node<Integer>(1);
        tree.root.left = new Tree.Node<Integer>(2);
        tree.root.right = new Tree.Node<Integer>(3);
        tree.root.left.right = new Tree.Node<Integer>(4);
        tree.root.right.left = new Tree.Node<Integer>(5);

        System.out.print("Inorder: ");
        tree.inorder();
        System.out.println();

        System.out.print("Inorder: ");
        tree.inorderIter();
        System.out.println();

        System.out.print("Preorder: ");
        tree.preorder();
        System.out.println();

        System.out.print("Postorder: ");
        tree.postorder();
        System.out.println();

        System.out.print("Inorder: ");
        for (var node : tree) {
            System.out.print(node + " ");
        }
        System.out.println();

        String out = "";
        out = serialize(tree.root, out);
        System.out.println("Serialized tree: " + out);

        Tree.Node<Integer> outRoot = deserialize(out.split(" "), new int[]{0});
        Tree<Integer> outTree = new Tree<>();
        outTree.root = outRoot;
        System.out.print("Inorder Traversal: ");
        outTree.inorder();
        System.out.println();

        System.out.println("Constructing Tree");
        List<Integer> inorder = tree.getInorder();
        System.out.println("Inorder " + inorder);
        List<Integer> preorder = tree.getPreorder();
        System.out.println("Preorder " + preorder);
        Tree<Integer> newRoot = new Tree<Integer>(constructTree(inorder, preorder, new int[]{0}));
        System.out.print("Inorder(Constructed Tree): ");
        newRoot.inorder();
        System.out.println();

        System.out.println("Construct bst");
        Tree<Integer> bst = new Tree<>();
        bst.root = new Tree.Node<Integer>(5);
        bst.root.left = new Tree.Node<Integer>(3);
        bst.root.left.left = new Tree.Node<Integer>(1);
        bst.root.left.right = new Tree.Node<Integer>(4);
        bst.root.right = new Tree.Node<Integer>(9);
        bst.root.right.left = new Tree.Node<Integer>(7);

        System.out.print("Inorder(bst): ");
        bst.inorder();
        System.out.println();

        String outbst = "";
        outbst = serializeBST(bst.root, outbst);
        System.out.println("Serialized bst: " + outbst);

        Tree<Integer> newbst = new Tree<>(deserializeBST(outbst.split(" "), new int[]{0}, Integer.MIN_VALUE, Integer.MAX_VALUE));
        System.out.print("Deserialized bst Inorder: ");
        newbst.inorder();
        System.out.println();
    }

    private static Tree.Node<Integer> deserializeBST(String[] s, int[] pos, int mn, int mx) {
        if (pos[0] >= s.length) return null;
        Integer item = Integer.parseInt(s[pos[0]]);
        if (item > mn && item < mx) {
            pos[0]++;
            Tree.Node<Integer> cur = new Tree.Node<>(item);
            cur.left = deserializeBST(s, pos, mn, cur.val);
            cur.right = deserializeBST(s, pos, cur.val, mx);
            return cur;
        }
        return null;
    }

    private static String serializeBST(Tree.Node<Integer> bst, String outbst) {
        if (bst == null) return outbst;
        if (!outbst.isEmpty()) outbst += " ";
        outbst += bst.toString();

        outbst = serializeBST(bst.left, outbst);
        outbst = serializeBST(bst.right, outbst);

        return outbst;
    }

    private static Tree.Node<Integer> constructTree(List<Integer> inorder, List<Integer> preorder, int[] pos) {
        if (pos[0] >= preorder.size()) return null;
        Integer curElem = preorder.get(pos[0]);
        pos[0]++;

        int index = getIndex(inorder, curElem);
        if (index == -1) return null;

        Tree.Node<Integer> curNode = new Tree.Node<>(curElem);
        curNode.left = constructTree(new ArrayList<>(inorder.subList(0, index)), preorder, pos);
        curNode.right = constructTree(new ArrayList<>(inorder.subList(index + 1, inorder.size())), preorder, pos);

        return curNode;
    }

    private static int getIndex(List<Integer> inorder, Integer curElem) {
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder.get(i) == curElem) return i;
        }
        return -1;
    }

    private static Tree.Node<Integer> deserialize(String[] out, int[] pos) {
        if (out.length == pos[0]) return null;
        String str = out[pos[0]];
        pos[0] += 1;
        if (str.equals("#")) return null;
        Tree.Node<Integer> node = new Tree.Node<Integer>(Integer.parseInt(str));
        node.left = deserialize(out, pos);
        node.right = deserialize(out, pos);

        return node;
    }

    private static String serialize(Tree.Node<Integer> node, String out) {
        if (node == null) {
            if (!out.isEmpty()) out += " #";
            return out;
        }
        if (!out.isEmpty()) out += " ";
        out += node.toString();
        out = serialize(node.left, out);
        out = serialize(node.right, out);
        return out;
    }
}

class Tree<T> implements Iterable {

    Node<T> root = null;

    Tree(Node<T> cur) {
        root = cur;
    }

    Tree() {
    }

    @Override
    public Iterator iterator() {
        return new TreeIterator(root);
    }

    public List<T> getInorder() {
        List<T> res = new ArrayList<>();
        getInorderInternal(root, res);

        return res;
    }

    public List<T> getPreorder() {
        List<T> res = new ArrayList<>();
        getPreorderInternal(root, res);

        return res;
    }

    private void getPreorderInternal(Node<T> node, List<T> res) {
        if (node == null) return;
        res.add(node.val);
        getPreorderInternal(node.left, res);
        getPreorderInternal(node.right, res);
    }

    private void getInorderInternal(Node<T> node, List<T> res) {
        if (node == null) return;
        getInorderInternal(node.left, res);
        res.add(node.val);
        getInorderInternal(node.right, res);
    }

    private void inorder_internal(Node node) {
        if (node == null) return;
        inorder_internal(node.left);
        System.out.print(node.toString() + " ");
        inorder_internal(node.right);
    }

    private void preorder_internal(Node node) {
        if (node == null) return;
        System.out.print(node.toString() + " ");
        preorder_internal(node.left);
        preorder_internal(node.right);
    }

    private void postorder_internal(Node node) {
        if (node == null) return;
        postorder_internal(node.left);
        postorder_internal(node.right);
        System.out.print(node.toString() + " ");
    }

    static class Node<T> {
        T val;
        Node left, right;

        Node(T val) {
            this.val = val;
        }

        @Override
        public String toString() {
            return val.toString();
        }
    }

    class TreeIterator implements Iterator {
        private final Stack<Node<T>> st = new Stack<>();
        private Node<T> node = null;

        TreeIterator(Node<T> node) {
            this.node = node;
        }

        @Override
        public boolean hasNext() {
            while (node != null) {
                st.push(node);
                node = node.left;
            }
            return !st.empty();
        }

        @Override
        public Object next() {
            var item = st.pop();
            node = item.right;
            return item;
        }
    }

    void inorder() {
        inorder_internal(root);
    }

    void inorderIter() {
        Stack<Node<T>> st = new Stack();
        Node<T> cur = root;

        while (!st.empty() || cur != null) {
            while (cur != null) {
                st.push(cur);
                cur = cur.left;
            }
            if (st.empty()) break;
            cur = st.pop();
            System.out.print(cur + " ");
            cur = cur.right;
        }
    }

    void preorder() {
        preorder_internal(root);
    }

    void postorder() {
        postorder_internal(root);
    }
}
