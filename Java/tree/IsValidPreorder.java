package Java.tree;

import Java.types.Pair;
import Java.types.TreeNode;

import java.util.Arrays;
import java.util.List;
import java.util.Stack;

/*
Amazon

Given an ArrayList of Nodes, with each Node having an ID and a parent ID,
determine whether the List is given in preorder
 */
public class IsValidPreorder {
    public static void test() {
        TreeNode<Integer> node1 = new TreeNode<>(3);
        TreeNode<Integer> node2 = new TreeNode<>(2);
        TreeNode<Integer> node3 = new TreeNode<>(6);
        TreeNode<Integer> node4 = new TreeNode<>(2);
        TreeNode<Integer> node5 = new TreeNode<>(1);
        TreeNode<Integer> node6 = new TreeNode<>(5);

        List<Pair<TreeNode<Integer>, TreeNode<Integer>>> l = Arrays.asList(
                new Pair(node1, null),
                new Pair(node2, node1),
                new Pair(node3, node2),
                new Pair(node4, node2),
                new Pair(node5, node1),
                new Pair(node6, node5));

        System.out.println("Is Valid Preorder: " + isValidPreorder(l));
    }

    private static boolean isValidPreorder(List<Pair<TreeNode<Integer>, TreeNode<Integer>>> l) {
        if (l.isEmpty())
            return true;
        if (l.get(0).second != null)
            return false;

        Stack<Pair<TreeNode<Integer>, TreeNode<Integer>>> st = new Stack<>();
        st.push(l.get(0));

        for (int i = 1; i < l.size();) {
            if (st.empty())
                return false;
            else if (l.get(i).second != st.peek().first)
                st.pop();
            else
                st.push(l.get(i++));
        }

        return true;
    }
}


/*
class Node:
    def __init__(self, ID, parent):
        self.ID = ID
        self.parentID = parent
        self.left = None
        self.right = None

#function to identify if given is preorder
'''
Create a stack to store nodes in the current path when traversing.
Push node[i] into stack once node[i] is verified to be valid (valid only when parent of node[i] is in stack.
In preorder a parent must show up earlier than its child)
Whenever stack top is not the parent of node[i], pop until parent of node[i] is at stack top. Push node[i].
If all nodes popped but parent of node[i] still not found, then node[i] is not in preorder sequence.
'''
def isPreorder(nodes):
    if not nodes:
        return True

    st = [nodes[0].ID]
    i = 1
    while i < len(nodes):
        if not st:
            return False
        if st[-1] is nodes[i].parentID:
            st.append(nodes[i].ID)
            i += 1
        else:
            st.pop()
    return True
 */