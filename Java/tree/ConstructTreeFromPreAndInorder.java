package Java.tree;

public class ConstructTreeFromPreAndInorder {
    private int preIndex = 0;

    public static void test() {
        ConstructTreeFromPreAndInorder obj = new ConstructTreeFromPreAndInorder();
        char[] in = { 'D', 'B', 'E', 'A', 'F', 'C' };
        char[] pre = { 'A', 'B', 'D', 'E', 'C', 'F' };
        Node root = obj.construct(pre, in);

        obj.inorder(root);
        System.out.println();
    }

    public Node construct(char[] pre, char[] in) {
        Node node = null;
        try {
            node = construct(pre, in, 0, in.length - 1);
        } catch (Exception e) {
            System.out.println(e);
        }
        return node;
    }

    private Node construct(char[] pre, char[] in, int l, int r) throws Exception {
        if (preIndex >= pre.length || l > r)
            return null;

        var curNode = new Node(pre[preIndex++]);
        var inIndex = find(in, l, r, curNode.val);
        if (inIndex == -1)
            throw new Exception("Unknown exception");

        curNode.left = construct(pre, in, l, inIndex - 1);
        curNode.right = construct(pre, in, inIndex + 1, r);

        return curNode;
    }

    private int find(char[] in, int l, int r, char ch) {
        for (var i = l; i <= r; i++) {
            if (in[i] == ch)
                return i;
        }
        return -1;
    }

    private void inorder(Node cur) {
        if (cur != null) {
            inorder(cur.left);
            System.out.print(cur.val + " ");
            inorder(cur.right);
        }
    }

    class Node {
        char val;
        Node left, right;

        Node(char val) {
            this.val = val;
            this.left = this.right = null;
        }
    }
}
