package Java.tree;

public class CountNodesInBST {
    public static void test() {
        CountNodesInBST obj = new CountNodesInBST();
        BinarySearchTree<Integer> bst = new BinarySearchTree<>();
        bst.insert(5);
        bst.insert(3);
        bst.insert(1);
        bst.insert(4);
        bst.insert(2);
        bst.insert(6);
        bst.insert(7);
        bst.insert(8);
        bst.insert(9);
        bst.insert(10);

        int count = obj.count(bst.getNode(), 4, 6);
        System.out.println("Count = " + count);
    }

    private int count(Node<Integer> root, int from, int to) {
        if (root == null)
            return 0;

        int r = less(root, to);
        int l = less(root, from - 1);

        return r - l;
    }

    private int less(Node<Integer> root, int val) {
        if (root == null)
            return 0;

        if (val >= root.val)
            return 1 + size(root.left) + less(root.right, val);
        return less(root.left, val);
    }

    private int size(Node<Integer> left) {
        if (left == null)
            return 0;

        return left.sz;
    }
}
