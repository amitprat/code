#include "../Header.h"

/*
given preorder traversal [5,3,2,4,8,7,9] of a BST, how do we identify the leaf nodes without building the tree ?

@Anonymous Thanks for the reply!
Please try other use cases like, only single leaf node
*/

static void findLeafs(int arr[], int length)
{
    if (length == 0)
        return;

    stack<int> stack;
    for (int n = 1, c = 0; n < length; n++, c++)
    {
        if (arr[c] > arr[n])
        {
            stack.push(arr[c]);
        }
        else
        {
            bool found = false;
            while (!stack.empty())
            {

                if (arr[n] > stack.top())
                {
                    stack.pop();
                    found = true;
                }
                else
                    break;
            }
            if (found)
                cout << arr[c] << " ";
        }
    }
    cout << arr[length - 1] << endl;
}