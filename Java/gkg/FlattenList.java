package programs.gkg;

public class FlattenList {
    public static void test() {
        FlattenList obj = new FlattenList();
        Node<Integer> root = obj.new Node<>(1);
        root.down = obj.new Node<>(2);
        root.down.next = obj.new Node<>(3);
        root.down.down = obj.new Node<>(4);
        root.down.down.next = obj.new Node<>(5);
        root.down.down.down = obj.new Node<>(6);
        root.next = obj.new Node<>(7);
        root.next.next = obj.new Node<>(8);
        root.next.next.next = obj.new Node<>(9);
        root.next.next.next.down = obj.new Node<>(10);
        root.next.next.next.down.next = obj.new Node<>(11);

        Node<Integer> result = obj.flatten(root);
        print(result);
    }

    private static void print(Node<Integer> result) {
        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
        System.out.println();
    }

    private Node<Integer> flatten(Node<Integer> root) {
        if (root == null) return root;

        root.next = flatten(root.next);
        root.down = flatten(root.down);
        root.next = merge(root.down, root.next);

        return root;
    }

    private Node<Integer> merge(Node<Integer> down, Node<Integer> next) {
        if (down == null) return next;

        Node<Integer> result = null;
        if (next == null || (down.val <= next.val)) {
            result = down;
            result.next = merge(down.next, next);
        } else {
            result = next;
            result.next = merge(down, next.next);
        }
        result.down = null;
        return result;
    }

    private class Node<T> {
        public T val;
        public Node next;
        public Node down;

        public Node(T val) {
            this.val = val;
            this.next = null;
            this.down = null;
        }

        @Override
        public String toString() {
            return val.toString();
        }
    }
}
