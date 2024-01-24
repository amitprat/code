package Java.tree;

public class Node<T> {
    T val;
    Node<T> left;
    Node<T> right;
    int sz;

    Node(T val) {
        this.val = val;
        this.left = null;
        this.right = null;
        this.sz = 1;
    }

    Node(T val, Node<T> left, Node<T> right) {
        this.val = val;
        this.left = left;
        this.right = right;
        this.sz = 1;
    }

    @Override
    public String toString() {
        return val.toString();
    }
}
