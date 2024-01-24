/*
Given 2 arrays.Imagine you are making bst from each array.u need to tell whether 2 bsts will be identical or not without actually constructing the tree.
Ex:
2 3 1
2 1 3
will construct the same tree
A1[]={2,1,3}
2
1 3

A2[]={2,3,1}
2
1 3

https://www.careercup.com/question?id=19016700
*/

/*

Assumption: All numbers are distinct (otherwise, you need to tell us about the BST insertion algorithm).

One solution (but essentially same as the tree compare solution in spirit): you can do something like quicksort:

Given Arrays A and B, check if A[0] = B[0] (if not, return false).

Now construct A_more, A_less and B_more, B_less where A_more contains elements of A which are > A[0] (and appear in the same order as they appear in A). This is basically the partition step in quicksort. Note that you need the partition to be stable. It is possible to do that in-place, but is very complex.

Now, recursively compare A_more, B_more and compare A_less and B_less. You can add optimizations to compare lengths of arrays to bail out quicker.

- Loler June 03, 2013 | FlagReply
0
of 0 votes
quick sort works .. but there is a catch ..
For the first time, we take first element as pivot from both arrays and divided the arrays..
For the 2nd iteration onwards, we have to take the same element as pivot in both arrays .. this needs O(n) time or we have to do some kind of pre-processing ...

Second approach is not accepted as it was stated in the question itself that we should give answer without constructing BSTs.

- bharat June 03, 2013 | Flag
1
of 1 vote
@Bharath: The catch is that you need a stable partition: The relative ordering of elements must not change. Once you do that, you can do recursively, by comparing the first elements of the two partitions you get. You don't have to do any other preprocessing.

If you actually look to take the same element as pivot (as you seem to suggest), then you will get wrong answers, counterexample:

1 2 3
1 3 2

- Loler June 03, 2013 | Flag
0
of 0 votes
How about using O(n) extra space to do partition in-place? Let quicksort's partition algorithm decide the correct position of an element only (Create a backup of original array before passing it to partition algorithm, then use it to partition stably).
Time complexity would be O(nlogn) which is same as original algorithm and space complexity would be O(n).

- Epic_coder June 04, 2013 | Flag
0
of 0 votes
@Epic_coder: Then by definition it is not in-place. The point of an in-place algorithm is to save space...

- Loler June 04, 2013 | Flag
0
of 0 votes
Very nice idea with partitioning, I was thinking about recursive check for left and right children, but qsort partitioning will do the work

- Tim1 June 05, 2013 | Flag
0
of 0 votes
Nice logic! Here is the working python code using quicksort:


A = [2,3,1,4,5,6,7,8]
B = [2,1,3,8,7,6,5,4]

def find_if_equal(X,Y):
    if ((len(X) != len(Y)) or (X[0]!=Y[0])):
        return False
    else:
        if(len(X) == 1): return True
        Amin = [x for x in X[1:] if x<=X[0]]
        Amax = [x for x in X[1:] if x>X[0]]
        Bmin = [y for y in Y[1:] if y<=Y[0]]
        Bmax = [y for y in Y[1:] if y>Y[0]]
        
        if(Amin):
            if(Bmin.count(Amin[0]) == 0): return False
            if(len(Bmin)>;1 and Amin[0]!= Bmin[0]):
                i = Bmin.index(Amin[0]) 
		Bmin[0],Bmin[i] = Bmin[i],Bmin[0]
            if (not find_if_equal(Amin,Bmin)): return False
        if(Amax):
            if(Bmax.count(Amax[0]) == 0): return False
            if((len(Bmax)>;1) and (Amax[0]!=Bmax[0])):
                i = Bmax.index(Amax[0])
                Bmax[0],Bmax[i] = Bmax[i],Bmax[0] 
            if (not find_if_equal(Amax,Bmax)): return False

        return True

if (find_if_equal(A,B)):
    print("Two arrays A:{} and B:{} will make identical Binary Search Trees".format(A,B))
else:
    print("Two arrays A:{} and B:{} will not make identical BST's".format(A,B))

*/