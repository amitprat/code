package Java.tree;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Stack;

public class BinarySearchTree<T extends Comparable<T>> implements Iterable<T> {
    private Node<T> root = null;

    public static void test() {
        BinarySearchTree<Integer> obj = new BinarySearchTree<Integer>();
        obj.insert(1);
        obj.insert(5);
        obj.insert(2);
        obj.insert(6);
        obj.insert(3);

        System.out.print("List: ");
        List<Integer> result = obj.inorder();
        for (Integer item : result) {
            System.out.print(item + " ");
        }
        System.out.println();

        try {
            obj.delete(1);
        } catch (Exception e) {

        }

        obj.insert(2);
        obj.insert(8);
        obj.insert(100);
        obj.insert(-100);

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();

        try {
            obj.delete(100);
        } catch (Exception e) {

        }

        try {
            obj.delete(200);
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();

        try {
            System.out.println("programs.tree.Node 1 found? " + obj.search(1));
        } catch (Exception e) {
            System.out.println(e);
        }

        try {
            System.out.println("programs.tree.Node 1 found? " + obj.search(8));
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();
    }

    public Node<T> getNode() {
        return root;
    }

    @Override
    public Iterator<T> iterator() {
        return new BinarySearchTreeIterator<T>(root);
    }

    public boolean search(T key) throws Exception {
        return searchInternal(root, key);
    }

    private boolean searchInternal(Node<T> cur, T key) throws Exception {
        if (cur == null) {
            throw new Exception("Key not found " + key.toString());
        }

        if (cur.val.compareTo(key) == 0)
            return true;

        if (key.compareTo(cur.val) < 0)
            return searchInternal(cur.left, key);
        return searchInternal(cur.right, key);
    }

    public void insert(T val) {
        root = insertInternal(root, val);
    }

    private Node<T> insertInternal(Node<T> cur, T key) {
        if (cur == null)
            return new Node<T>(key);
        if (cur.val == key)
            return cur;

        if (key.compareTo(cur.val) < 0)
            cur.left = insertInternal(cur.left, key);
        else if (key.compareTo(cur.val) > 0)
            cur.right = insertInternal(cur.right, key);

        cur.sz++;

        return cur;
    }

    public void delete(T val) throws Exception {
        root = deleteInternal(root, val);
    }

    private Node<T> deleteInternal(Node<T> cur, T key) throws Exception {
        if (cur == null) {
            throw new Exception(("Key not found while deleting " + key.toString()));
        }

        if (cur.val == key)
            cur = deleteCurrent(cur);
        else if (key.compareTo(cur.val) < 0)
            cur.left = deleteInternal(cur.left, key);
        else
            cur.right = deleteInternal(cur.right, key);

        cur.sz--;

        return cur;
    }

    private Node<T> deleteCurrent(Node<T> cur) throws Exception {
        // if leaf node, return null directly.
        if (cur.left == null && cur.right == null)
            return null;

        // if left or right is null, delete current node and return non-empty left or
        // right.
        if (cur.left == null || cur.right == null) {
            return cur.left != null ? cur.left : cur.right;
        }

        // find successor
        Node<T> successor = cur.right;
        while (successor.left != null)
            successor = successor.left;

        // update the successory value to current value
        cur.val = successor.val;

        // start deleting the successor value on right
        cur.right = deleteInternal(cur.right, successor.val);

        return cur;
    }

    List<T> inorder() {
        List<T> result = new ArrayList<>();
        inorderInternal(root, result);

        return result;
    }

    private void inorderInternal(Node<T> cur, List<T> result) {
        if (cur == null)
            return;

        inorderInternal(cur.left, result);
        result.add(cur.val);
        inorderInternal(cur.right, result);
    }
}

class BinarySearchTreeIterator<T> implements Iterator<T> {
    private final Stack<Node<T>> stack = new Stack<Node<T>>();
    private Node<T> root;

    BinarySearchTreeIterator(Node<T> root) {
        this.root = root;
    }

    @Override
    public boolean hasNext() {
        return !stack.empty() || root != null;
    }

    @Override
    public T next() {
        if (root != null) {
            populateStack();
        }

        root = stack.pop();
        T val = root.val;
        root = root.right;

        return val;
    }

    private void populateStack() {
        while (root != null) {
            stack.push(root);
            root = root.left;
        }
    }
}
