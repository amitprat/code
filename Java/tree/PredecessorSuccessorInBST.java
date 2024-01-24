package Java.tree;

public class PredecessorSuccessorInBST {
    public static void test() {
        PredecessorSuccessorInBST obj = new PredecessorSuccessorInBST();
        Node<Integer> root = new Node<Integer>(5);
        root.left = new Node<Integer>(3);
        root.right = new Node<Integer>(8);
        root.left.left = new Node<Integer>(2);
        root.left.left.left = new Node<Integer>(1);
        root.left.right = new Node<Integer>(4);
        root.right.right = new Node<Integer>(9);
        root.right.left = new Node<Integer>(7);

        for (int val = 0; val < 11; val++) {
            PredSuc preSuc = obj.new PredSuc();
            obj.findPredSuccessor(root, val, preSuc);
            System.out.println("Predecessor and Successor of val:" + val + " = " + preSuc);
        }

        for (int val = 0; val < 11; val++) {
            PredSuc preSuc = obj.new PredSuc();
            obj.predecessor(root, val, preSuc);
            obj.successor(root, val, preSuc);
            System.out.println("Predecessor and Successor of val:" + val + " = " + preSuc);
        }
    }

    // find predecessor and successor
    void findPredSuccessor(Node<Integer> cur, int val, PredSuc res) {
        if (cur == null)
            return;

        if (val < cur.val) {
            res.suc = cur;
            findPredSuccessor(cur.left, val, res);
        } else if (val > cur.val) {
            res.pre = cur;
            findPredSuccessor(cur.right, val, res);
        } else {
            // find predecessor on left
            var tmp = cur.left;
            while (tmp != null && tmp.right != null)
                tmp = tmp.right;
            if (tmp != null)
                res.pre = tmp;

            // find successor on right
            tmp = cur.right;
            while (tmp != null && tmp.left != null)
                tmp = tmp.left;
            if (tmp != null)
                res.suc = tmp;
        }
    }

    // find successor of node
    public void successor(Node<Integer> cur, int val, PredSuc res) {
        if (cur == null)
            return;

        if (val < cur.val) {
            res.suc = cur;
            successor(cur.left, val, res);
        } else if (val > cur.val) {
            successor(cur.right, val, res);
        } else {
            var tmp = cur.right;
            while (tmp != null && tmp.left != null)
                tmp = tmp.left;

            if (tmp != null)
                res.suc = tmp;
        }
    }

    // find predecessor of node
    public void predecessor(Node<Integer> cur, int val, PredSuc res) {
        if (cur == null)
            return;

        // if value is greater then current node then look on right side
        if (val > cur.val) {
            res.pre = cur;
            predecessor(cur.right, val, res);
        } else if (val < cur.val) {
            predecessor(cur.left, val, res);
        } else {
            Node<Integer> tmp = cur.left;
            while (tmp != null && tmp.right != null)
                tmp = tmp.right;

            if (tmp != null)
                res.pre = tmp;
        }
    }

    class PredSuc {
        Node<Integer> pre = null;
        Node<Integer> suc = null;

        @Override
        public String toString() {
            return "{Predecessor=" + val(pre) + ", Successor=" + val(suc) + "}";
        }

        int val(Node<Integer> cur) {
            return cur == null ? -1 : cur.val;
        }
    }
}
