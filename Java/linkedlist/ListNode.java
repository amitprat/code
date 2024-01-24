package programs.linkedlist;

public class ListNode<T> {
    public T val;
    public ListNode next;

    public ListNode(T val) {
        this.val = val;
        this.next = null;
    }

    @Override
    public String toString() {
        return val.toString();
    }
}
