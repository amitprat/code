//g++  5.4.0

#include <iostream>
#include <string>
#include <list>
#include <stack>
using namespace std;

class Tree
{
    public:
        int val;
        Tree *left, *right;
        Tree(int val, Tree *left=nullptr, Tree *right=nullptr) : val(val), left(left), right(right) {}
};

class BinarySearchTree
{
    private:
        void preorder(Tree *tmp, list<Tree *>& out)
        {
            if(tmp)
            {
                out.push_back(tmp);
                preorder(tmp->left, out);
                preorder(tmp->right,out);
            }
        }

    public:
        Tree *root = nullptr;
        list<Tree *> preorder()
        {
            list<Tree *> res;
            Tree *tmp = root;
            preorder(tmp, res);
                
            return res;
        }
};

void reconstruct(list<Tree *> pre, BinarySearchTree& obj)
{
    stack<Tree *> st;
    Tree* val = nullptr;
    st.push(val = pre.front()); pre.pop_front();
    cout<<"Values : " << val->val<<" ";
    
    while(!st.empty() && !pre.empty())
    {
        if(pre.front() > st.top()) { st.push(val = pre.front()); pre.pop_front(); }
        else {
            Tree *tmp = nullptr;
            while(!st.empty() && st.top() < pre.front()) {
                tmp = st.top(); st.pop();
            }
            if(tmp != nullptr) { tmp->right = val = pre.front(); st.push(tmp); pre.pop_front(); }
            else { st.push(val = pre.front()); pre.pop_front(); }
        }
        cout<<val->val<<" ";
    }
    cout<<endl;
    obj.root = st.top(); st.pop();
}

int main()
{
    BinarySearchTree obj;
    obj.root = new Tree(5);
    obj.root->left = new Tree(4);
    obj.root->left->left = new Tree(1);
    obj.root->left->left->right = new Tree(2);
    obj.root->right = new Tree(7);
    obj.root->right->left = new Tree(6);
    obj.root->right->right = new Tree(8);
    obj.root->right->right->right = new Tree(9);
    
    auto res = obj.preorder();
    for(auto i : res) cout<<i->val<<" ";
    cout<<endl;
    
    BinarySearchTree other;
    reconstruct(res, other);
    
    res = obj.preorder();
    for(auto i : res) cout<<i->val<<" ";
    cout<<endl;
    
    return 0;
}