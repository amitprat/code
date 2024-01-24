package Java.tree;

import Java.types.Pair;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

public class FindPairInBST {
    public static void test() {
        FindPairInBST obj = new FindPairInBST();
        Node<Integer> root = new Node<Integer>(15);
        root.left = new Node<Integer>(10);
        root.right = new Node<Integer>(20);
        root.left.left = new Node<Integer>(8);
        root.left.right = new Node<Integer>(12);
        root.right.left = new Node<Integer>(16);
        root.right.right = new Node<Integer>(25);

        int sum = 28;
        Pair<Integer, Integer> res = obj.findPairUsingStack(root, sum);
        System.out.println(res);

        res = obj.findPair(root, sum);
        System.out.println(res);
    }

    private Pair<Integer, Integer> findPairUsingStack(Node<Integer> root, int sum) {
        Stack<Node<Integer>> st1 = new Stack<>();
        Stack<Node<Integer>> st2 = new Stack<>();
        boolean moveRight = true, moveLeft = true;
        Node<Integer> left = root, right = root;

        while (true) {
            if (moveLeft) {
                while (left != null) {
                    st1.add(left);
                    left = left.left;
                }

                if (st1.empty())
                    break;

                left = st1.pop();
                moveLeft = false;
            }

            if (moveRight) {
                while (right != null) {
                    st2.add(right);
                    right = right.right;
                }

                if (st2.empty())
                    break;

                right = st2.pop();
                moveRight = false;
            }

            if ((Integer) left.val > (Integer) right.val)
                break;

            if ((Integer) left.val + (Integer) right.val == sum) {
                return new Pair<>((Integer) left.val, (Integer) right.val);
            } else if ((Integer) left.val + (Integer) right.val > sum) {
                moveRight = true;
                right = right.left;
            } else {
                moveLeft = true;
                left = left.right;
            }
        }

        return new Pair<>();
    }

    private Pair<Integer, Integer> findPair(Node<Integer> root, int sum) {
        Set<Integer> set = new HashSet<>();
        Pair<Integer, Integer> res = new Pair<>();
        if (!findPair(root, sum, res, set)) {
            System.out.println("No pair found with given sum");
        }

        return res;
    }

    private boolean findPair(Node<Integer> root, int sum, Pair<Integer, Integer> res, Set<Integer> set) {
        if (root == null)
            return false;

        if (set.contains(sum - (Integer) root.val)) {
            res.first = sum - (Integer) root.val;
            res.second = (Integer) root.val;
            return true;
        }

        set.add((Integer) root.val);

        return findPair(root.left, sum, res, set) || findPair(root.right, sum, res, set);
    }
}
