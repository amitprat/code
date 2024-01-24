package Java.types;

public class TreeNode<T> {
    public T val;
    public TreeNode left, right;

    public TreeNode(T val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }

    @Override
    public String toString() {
        return "TreeNode{" +
                "val=" + val +
                ", left=" + left +
                ", right=" + right +
                '}';
    }
}
