package programs.linkedlist;

public class SwapKthNode {
    public static void test() {
        ListNode<Integer> l = new ListNode<>(1);
        l.next = new ListNode<>(2);
        l.next.next = new ListNode<>(3);
        l.next.next.next = new ListNode<>(4);
        print(l);

        l = swapKthNodes(l, 1);

        print(l);
    }

    private static ListNode<Integer> swapKthNodes(ListNode<Integer> l, int k) {
        ListNode<Integer> ptr1 = null, ptr2 = null;
        ListNode<Integer> prevPtr1 = null, prevPtr2 = null;
        ListNode<Integer> ptr3 = l;
        int cnt = 0;

        while (ptr3 != null) {
            cnt++;
            if (cnt < k) prevPtr1 = ptr3;
            else if (cnt == k) {
                ptr1 = ptr3;
                ptr2 = l;
            } else if (cnt > k) {
                prevPtr2 = ptr2;
                ptr2 = ptr2.next;
            }
            ptr3 = ptr3.next;
        }
        System.out.println(ptr1.toString() + ", " + ptr2.toString());

        if (prevPtr1 != null) prevPtr1.next = ptr2;
        if (prevPtr2 != null) prevPtr2.next = ptr1;

        var tmp = ptr1.next;
        ptr1.next = ptr2.next;
        ptr2.next = tmp;

        if (k == 1) l = ptr2;
        else if (k == cnt) l = ptr1;

        return l;
    }

    private static void print(ListNode<Integer> l) {
        while (l != null) {
            System.out.print(l + " ");
            l = l.next;
        }
        System.out.println();
    }
}
