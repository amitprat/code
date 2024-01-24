package programs.careercup;

import programs.linkedlist.ListNode;

import java.util.Stack;

public class ChangeLinkedList {
    public static void test() {
        ChangeLinkedList obj = new ChangeLinkedList();
        ListNode<Integer> root = new ListNode<>(1);
        root.next = new ListNode(2);
        root.next.next = new ListNode(3);
        root.next.next.next = new ListNode(4);
        root.next.next.next.next = new ListNode(5);

        obj.swapNodes1(root);
        obj.print(root);
    }

    private void swapNodes1(ListNode<Integer> root) {
        ListNode<Integer> fast = root, slow = root;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;
        }

        fast = slow.next;
        slow.next = null;

        fast = reverse(fast);

        merge(root, fast);
    }

    private ListNode<Integer> reverse(ListNode<Integer> node) {
        ListNode<Integer> prev = null;
        while (node != null) {
            var next = node.next;
            node.next = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    private void merge(ListNode<Integer> first, ListNode<Integer> second) {
        while (first != null && second != null) {
            var next = first.next;
            first.next = second;
            second = second.next;
            first.next.next = next;
            first = next;
        }
    }

    private void swapNodes(ListNode<Integer> root) {
        int l = length(root);
        Stack<ListNode<Integer>> st = new Stack<>();
        int m = l / 2;
        ListNode<Integer> tmp = root;
        while (tmp != null) {
            if (m < 0) st.push(tmp);
            tmp = tmp.next;
            m--;
        }

        tmp = root;
        while (!st.empty()) {
            var next = tmp.next;
            tmp.next = st.pop();
            tmp.next.next = next;
            tmp = tmp.next.next;
        }
        tmp.next = null;
    }

    private void print(ListNode<Integer> root) {
        while (root != null) {
            System.out.printf("%d, ", root.val);
            root = root.next;
        }
        System.out.println();
    }

    private int length(ListNode<Integer> root) {
        ListNode<Integer> tmp = root;
        int len = 0;
        while (tmp != null) {
            len++;
            tmp = tmp.next;
        }

        return len;
    }
}
