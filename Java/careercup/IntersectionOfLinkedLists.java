package programs.careercup;

import java.util.HashSet;
import java.util.Set;

/*
https://www.careercup.com/question?id=13196682

Find the intersection of two linked list given their head pointer.
Constraint: You can only traverse a linked list only once.
 */

public class IntersectionOfLinkedLists {
    class Node {
        public int val;
        public Node next = null;

        public Node(int val) {
            this.val = val;
        }
    }

    public static void test() {
        IntersectionOfLinkedLists obj = new IntersectionOfLinkedLists();
        obj.internalTest();
    }

    public void internalTest() {
        Node head1 = new Node(10);
        Node head2 = new Node(3);
        head2.next = new Node(6);
        head2.next.next = new Node(9);
        head1.next = head2.next.next.next = new Node(15);
        head1.next.next = new Node(30);

        System.out.println("Intersection node: " + getIntersection2(head1, head2));
    }

    private int getIntersection1(Node head1, Node head2) {
        int l1 = length(head1);
        int l2 = length(head2);
        int d = l1-l2;
        while(d > 0) {
            head1 = head1.next;
            d--;
        }
        while(d < 0) {
            head2 = head2.next;
            d++;
        }

        while(head1 != null && head2 != null && head1.val != head2.val) {
            head1 = head1.next;
            head2 = head2.next;
        }

        return head1.val;
    }

    private int getIntersection2(Node head1, Node head2) {
        Set<Node> set = new HashSet<>();
        while(head1 != null) {
            set.add(head1);
            head1 = head1.next;
        }

        while(head2 != null && !set.contains(head2)) {
            head2 = head2.next;
        }

        return head2.val;
    }

    int length(Node node) {
        int l = 0;
        while(node != null) {
            node = node.next;
            l++;
        }
        return l;
    }
}
