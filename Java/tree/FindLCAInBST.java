package Java.tree;

import Java.types.Triplet;

public class FindLCAInBST {
    public static void test() {
        FindLCAInBST obj = new FindLCAInBST();
        Node<Integer> root = new Node<Integer>(5);
        root.left = new Node<Integer>(3);
        root.right = new Node<Integer>(8);
        root.left.left = new Node<Integer>(2);
        root.left.left.left = new Node<Integer>(1);
        root.left.right = new Node<Integer>(4);
        root.right.right = new Node<Integer>(9);
        root.right.left = new Node<Integer>(7);

        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.toString(), root.right.toString(), obj.lca(root, root.left, root.right).toString());
        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.toString(), root.right.toString(), obj.lca1(root, root.left, root.right).toString());

        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.toString(), root.left.right.toString(), obj.lca(root, root.left, root.left.right).toString());
        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.toString(), root.left.right.toString(),
                obj.lca1(root, root.left, root.left.right).toString());

        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.right.toString(), root.right.toString(),
                obj.lca(root, root.left.right, root.right.right).toString());
        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.left.right.toString(), root.right.toString(),
                obj.lca1(root, root.left.right, root.right.right).toString());

        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.right.right.toString(), new Node<Integer>(10).toString(),
                obj.lca(root, root.right.right, new Node<Integer>(10)).toString());
        System.out.printf("LCA of node1:%s and node2:%s is %s.\n",
                root.right.right.toString(), new Node<Integer>(10).toString(),
                obj.lca1(root, root.right.right, new Node<Integer>(10)).toString());
    }

    public Node<Integer> lca(Node<Integer> cur, Node<Integer> node1, Node<Integer> node2) {
        if (cur == null)
            return null;

        if (node1.val < cur.val && node2.val < cur.val)
            return lca(cur.left, node1, node2);
        else if (node1.val > cur.val && node2.val > cur.val)
            return lca(cur.right, node1, node2);
        else {
            return cur;
        }
    }

    Triplet<Boolean, Boolean, Node<Integer>> lca1(Node<Integer> cur, Node<Integer> node1, Node<Integer> node2) {
        if (cur == null)
            return new Triplet<>(false, false, null);

        var res = new Triplet<Boolean, Boolean, Node<Integer>>(false, false, null);
        if (cur == node1)
            res.first = true;
        if (cur == node2)
            res.second = true;

        var left = lca1(cur.left, node1, node2);
        if (left.third != null)
            return left;
        var right = lca1(cur.right, node1, node2);
        if (right.third != null)
            return right;

        if (left.first || right.first)
            res.first = true;
        if (left.second || right.second)
            res.second = true;
        if (res.first && res.second)
            res.third = cur;

        return res;
    }
}
