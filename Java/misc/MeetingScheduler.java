package programs.misc;

public class MeetingScheduler {
    private final BinaryTree calendar = new BinaryTree();

    public static void test() {
        {
            MeetingScheduler scheduler = new MeetingScheduler();
            scheduler.schedule(900, 1100, "Task A");
            scheduler.schedule(1100, 1300, "Task B");
            scheduler.schedule(1330, 1500, "Task C");
            scheduler.schedule(1400, 1500, "Task D");

            scheduler.show();
            System.out.println();
        }

        {
            MeetingScheduler scheduler = new MeetingScheduler();
            scheduler.schedule(15, 20, "Task A");
            scheduler.schedule(10, 30, "Task B");
            scheduler.schedule(17, 19, "Task C");
            scheduler.schedule(5, 20, "Task D");
            scheduler.schedule(12, 15, "Task E");
            scheduler.schedule(30, 40, "Task F");
            scheduler.schedule(6, 7, "Task G");

            scheduler.show();
            System.out.println();
        }
    }

    private void show() {
        System.out.println();
        calendar.inorder();
    }

    /*
        private void schedule(int start, int end, String task) {
            if (calendar.overlap(start, end)) {
                System.out.println(String.format("Task {%s,%s,%s} overlaps. Meeting not scheduled", start, end, task));
            } else {
                calendar.insert(start, end, task);
                System.out.println(String.format("Meeting {%s,%s,%s} scheduled successfully", start, end, task));
            }
        }
    */
    private void schedule(int start, int end, String task) {
        var res = calendar.insert(start, end, task);
        if (!res) {
            System.out.println(String.format("Task {%s,%s,%s} overlaps. Meeting not scheduled", start, end, task));
        } else {
            System.out.println(String.format("Meeting {%s,%s,%s} scheduled successfully", start, end, task));
        }
    }
}

class IntervalTree {
    Node root = null;

    public void inorder() {
        inorder(root);
    }

    private void inorder(Node root) {
        if (root == null) return;
        inorder(root.left);
        System.out.println(root);
        inorder(root.right);
    }

    private Node insert(Node root, int start, int end, String task) {
        if (root == null) return new Node(start, end, task);

        if (start < root.start) root.left = insert(root.left, start, end, task);
        else root.right = insert(root.right, start, end, task);

        root.max = Math.max(root.max, end);

        return root;
    }

    private boolean overlap(Node root, int start, int end) {
        if (root == null) return false;
        if (doOverlap(root, start, end)) {
            System.out.println(String.format("Meeting {%s,%s} overlap with {%s,%s,%s}",
                    start, end, root.start, root.end, root.task));
            return true;
        }

        if (root.left != null && start <= root.left.max)
            return overlap(root.left, start, end);
        return overlap(root.right, start, end);
    }

    private boolean doOverlap(Node root, int start, int end) {
        return !(end <= root.start || start >= root.end);
    }

    class Node {
        int start, end, max;
        String task;
        Node left, right;

        Node(int start, int end, String task) {
            this.start = start;
            this.end = end;
            this.max = end;
            this.task = task;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "start=" + start +
                    ", end=" + end +
                    ", max=" + max +
                    ", task='" + task + '\'' +
                    '}';
        }
    }

    boolean overlap(int start, int end) {
        return overlap(root, start, end);
    }

    void insert(int start, int end, String task) {
        root = insert(root, start, end, task);
    }

    void add(int start, int end, String task) {
        insert(root, start, end, task);
    }
}

class BinaryTree {
    Node root = null;

    public void inorder() {
        inorder(root);
    }

    private void inorder(Node root) {
        if (root == null) return;
        inorder(root.left);
        System.out.println(root);
        inorder(root.right);
    }

    class Node {
        int start, end;
        String task;
        Node left, right;

        Node(int start, int end, String task) {
            this.start = start;
            this.end = end;
            this.task = task;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "start=" + start +
                    ", end=" + end +
                    ", task='" + task + '\'' +
                    '}';
        }
    }

    boolean insert(int start, int end, String task) {
        try {
            root = insert(root, start, end, task);
            return true;
        } catch (Exception e) {
            System.out.println(e);
            return false;
        }
    }

    Node insert(Node root, int start, int end, String task) throws Exception {
        if (root == null) return new Node(start, end, task);

        if (end <= root.start) root.left = insert(root.left, start, end, task);
        else if (start >= root.end) root.right = insert(root.right, start, end, task);
        else throw new Exception(String.format("Task {%s,%s,%s} overlaps with {%s,%s,%s}",
                    start, end, task, root.start, root.end, root.task));

        return root;
    }
}