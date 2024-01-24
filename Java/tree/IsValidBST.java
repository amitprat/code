package Java.tree;

public class IsValidBST {
    public static void test() {
        IsValidBST obj = new IsValidBST();
        Node<Integer> root = new Node<Integer>(5);
        root.left = new Node<Integer>(3);
        root.right = new Node<Integer>(8);
        root.left.left = new Node<Integer>(2);
        root.left.left.left = new Node<Integer>(1);
        root.left.right = new Node<Integer>(4);
        root.right.right = new Node<Integer>(9);
        root.right.left = new Node<Integer>(7);

        System.out.println("Is Valid BST = " + obj.isBST(root));
    }

    public boolean isBST(Node<Integer> cur) {
        return isBST(cur, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private boolean isBST(Node<Integer> cur, int mn, int mx) {
        if (cur == null)
            return true;
        if (cur.val < mn || cur.val > mx)
            return false;

        return isBST(cur.left, mn, cur.val) || isBST(cur.right, cur.val, mx);
    }
}
